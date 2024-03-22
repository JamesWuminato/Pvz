#include <algorithm>
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>

#include "Plant.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Game.hpp"
#include "Land.hpp"

using namespace std;

void Game::start(CoinPlant &coinPlant,HornPlant &hornPlant,BombPlant &bombPlant,HealPlant &healPlant)
{
    while (!gameEnd_) 
    {
        round();
    }//while

    if (winned_)
    {
        cout << "Congratulations! You have killed all zombies!" << endl;
    }//if
    else if(bombUsed_)
    {
        cout << "\n\nYou lose the game since you cannot use that many bomb plants!" << endl;
    }
    else
    {
        cout<<"\n\nOh no... You have no plant on the map"<<endl;
    }//else

    system("pause");
    system("cls");
}//Game::start

void Game::read_txt(const std::string &fileName,CoinPlant &coinPlant,HornPlant &hornPlant,BombPlant &bombPlant,HealPlant &healPlant)
{
    ifstream File(fileName);
    char plantType, dollarSign;
    std::string plantName;
    int cost, hp;
    int coinVisits, coinReward;
    int hornDamage;
    int healPoints;

    for (int i = 0; i < 4; ++i)
    {

        File >> plantType >> plantName >> dollarSign >> cost >> hp;
        if (plantType == 'C')
        {
            File >> coinVisits >> coinReward;
            coinPlant.set_properties(plantName, cost, hp, coinVisits, coinReward);
        }
        else if (plantType == 'S')
        {
            File >> hornDamage;
            hornPlant.set_properties(plantName, cost, hp, hornDamage);
        }
        else if (plantType == 'B')
        {
            hornDamage = 100;
            bombPlant.set_properties(plantName, cost, hp, hp);
        }
        else if (plantType == 'H')
        {
            File >> healPoints;
            healPlant.set_properties(plantName, cost, hp, healPoints);
        }
    }
}

void Game::read_game_settings()
{
    string input;
    numLands_=8;
    numZombies_=3;
    cout << "-----------------------------" << endl;
    cout << "|     Plants vs. Zombies     |" << endl;
    cout << "-----------------------------" << endl;
    cout << "Number of lands on the map (1-10, default: 8)...>";
    getline(cin,input);
    if(!input.empty())
    {
        istringstream iss(input);

        iss>>numLands_;
    }
    cout << "Number of zombies on the map (1-10, default: 3)...>";
    getline(cin,input);
    if(!input.empty())
    {
        istringstream iss(input);
        iss>>numZombies_;
    }
    cout << "=============================================================================" << endl;
    cout << "Plants vs. Zombies Rule:\n\n";
    cout << "How to win:\n";
    cout << "  (1) All zombies are dead.\n";
    cout << "  (2) At least one plant is live.\n";
    cout << "  (3) The number of dead bomb plants cannot exceed the number of zombies.\n\n";
    cout << "How to lose:\n";
    cout << "  All plants are dead.\n";
    cout << "=============================================================================" << endl;
    system("pause");
    system("cls");

    srand(time(NULL));

    player_.earn_money(150);
    map_ = Map(numLands_,0);
    for(int i=0;i<numZombies_;++i)
    {
        map_.add_zombie(new Zombie(i,rand() % numLands_));

    }
    map_.move_player_to(rand() % numLands_);
}

void Game::move_player()
{
    int place = map_.get_player_position();
    place = (place + (rand() % 6 + 1)) % numLands_;
    map_.move_player_to(place);

    if (map_.get_plant_on(place))
    {
        display();
        map_.get_plant_on(place)->visit(player_, map_.get_all_zombies(), map_.get_all_plants());
    }//if
}

void Game::move_zombies()
{   
    std::vector<Zombie*> allZombies = map_.get_all_zombies();

    
    for (const auto& zombie : allZombies)
    {   
        //Move zombie to new position
        int place = zombie->get_position();
        place = (place + (rand() % 3 + 1)) % numLands_;
        map_.move_zombie_to(zombie->get_id(),place);
        
        display();
        cout<<"Zombie ["<< zombie->get_id() << "] moves to land "<<place<<"."<<endl;

        Plant *plantWithZombie = map_.get_plant_on(zombie->get_position());

        if (plantWithZombie)
        {
            // Plant attacks zombie
            if (plantWithZombie->is_offensive())
            {
                std::cout << plantWithZombie->attack(zombie) << '\n';
                if (zombie->get_health() <= 0)
                {
                    std::cout << "Zombie is killed!" << std::endl;
                }//if
            }//if

            // Zombie attacks plant
            if (zombie->get_health() > 0 && plantWithZombie->get_health() > 0)
            {
                zombie->attack(plantWithZombie);
            }//if

            if (plantWithZombie->get_health() <= 0)
            {
                std::cout << "Plant " << plantWithZombie->get_type_name() << " is dead!" << std::endl;
            }//if
        }//if
        
        map_.remove_dead_plants();
        system("pause");
    }
    //std::cerr << "asdfasf\n";
    //system("pause");
    map_.remove_dead_zombies();
}

void Game::display() const
{
    system("cls");
    map_.display(numZombies_);
    cout << "------------------------------------------------\n"
         << "Zombie information:" << endl;
    std::vector<Zombie*> allZombies = map_.get_all_zombies();

    sort(allZombies.begin(), allZombies.end(), [](Zombie *a, Zombie *b) { return a->get_id() < b->get_id(); });


    for (const auto& zombie : allZombies)
    {
        string zombieStats = zombie->get_stats();
        cout << zombieStats << endl;
    }   
    cout<<"================================================"<<endl;
}//Game::display_zombies_stats

void Game::round()
{
    string input;
    display();

    if(player_.get_money() > 0 && map_.get_plant_on(map_.get_player_position()) == nullptr)
    {

        cout<<"[0] "<<CoinPlant::get_info()<<endl;
        cout<<"[1] "<<HornPlant::get_info()<<endl;
        cout<<"[2] "<<BombPlant::get_info()<<endl;
        cout<<"[3] "<<HealPlant::get_info()<<endl;
        cout<<endl;
        
        int choice=lastChoice_;
        cout<<"player $"<<player_.get_money()<<":    Enter your choice (4 to give up, default: " << lastChoice_ << ")...>";
        getline(cin,input);
        if(!input.empty())
        {
            istringstream iss(input);
            iss>>choice;
            if (choice < 0 || choice > 3)
            {
                choice = 4;
            }
            lastChoice_ = choice;
        }
        int place = map_.get_player_position();
        Plant* plantPtr=nullptr;
        switch (choice)
        {
            case 0:
                plantPtr = new CoinPlant();
                map_.add_plant(plantPtr);
                player_.buy(*plantPtr);
                cout<<"You have planted "<<CoinPlant::get_name()<<" at land "<<place<<" !"<<endl;
                break;
        
            case 1:
                plantPtr= new HornPlant();
                map_.add_plant(plantPtr);
                player_.buy(*plantPtr);
                cout<<"You have planted "<<HornPlant::get_name()<<" at land "<<place<<" !"<<endl;
                break;
            case 2:
                plantPtr= new BombPlant();
                map_.add_plant(plantPtr);
                player_.buy(*plantPtr);
                cout<<"You have planted "<<BombPlant::get_name()<<" at land "<<place<<" !"<<endl;
                break;
            case 3:
                plantPtr= new HealPlant();
                map_.add_plant(plantPtr);
                player_.buy(*plantPtr);
                cout<<"You have planted "<<HealPlant::get_name()<<" at land "<<place<<" !"<<endl;
                break;
            case 4:
                cout<<"You give up!"<<endl;
                break;
        }
        system("pause");
    }
    else if (map_.get_plant_on(map_.get_player_position()) == nullptr)
    {
        cout<<"You do not have enough money to plant anything!"<<endl;
        system("pause");
    }

    int numPlants = map_.get_all_plants().size();
    int numZombies = map_.get_all_zombies().size();
    
    if(numPlants ==0)
    {
        gameEnd_ = true;
        winned_ = false;
        bombUsed_ = false;
        return;
    }//if
    else if(numZombies == 0)
    {
        gameEnd_ = true;
        winned_ = true;
        bombUsed_ = false;
        return;
    }//else if
    

    // system("pause");
    move_zombies(); 
    move_player();
    
    numPlants = map_.get_all_plants().size();

    if(numPlants == 0)
    {
        gameEnd_=1;
        winned_ = false;
        bombUsed_ = false;
        return;
    }
    else if(BombPlant::get_dead_bomb_cnt()>(numZombies_/2))
    {
        gameEnd_ = true;
        winned_ = false;
        bombUsed_ = true;
        return;
    }
    // system("pause");
    system("cls");  
};
