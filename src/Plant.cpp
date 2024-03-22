#include <iostream>

#include "Plant.hpp"

std::string CoinPlant::name_ = "";
int CoinPlant::cost_ = 0;
int CoinPlant::maxHealth_ = 0;
int CoinPlant::visitNeed_ = 0;
int CoinPlant::reward_ = 0;

std::string HornPlant::name_ = "";
int HornPlant::cost_ = 0;
int HornPlant::maxHealth_ = 0;
int HornPlant::damage_ = 0;

std::string BombPlant::name_ = "";
int BombPlant::cost_ = 0;
int BombPlant::maxHealth_ = 0;
int BombPlant::damage_ = 0;
int BombPlant::deadBombCnt_ = 0;

std::string HealPlant::name_ = "";
int HealPlant::cost_ = 0;
int HealPlant::maxHealth_ = 0;
int HealPlant::healPoints_ = 0;

//***************************PLANT***************************//
Plant::Plant(int health, int position, std::string typeName, bool isOffensive): health_(health), position_(position), typeName_(typeName), isOffensive_(isOffensive) {}

int Plant::get_position() const
{
    return position_;
} // get_position

int Plant::get_health() const
{
    return health_;
}

bool Plant::is_offensive() const
{
    return isOffensive_;
}//Plant::is_offensive

const std::string& Plant::get_type_name() const
{
    return typeName_;
}//get_type_name

void Plant::move_to(int position)
{
    position_ = position;
} // move_to

void Plant::increse_health(int heal_points, int maxHealth)
{
    health_ += heal_points;
    if(health_ > maxHealth)health_ = maxHealth;
} // increse_health

void Plant::decrease_health(int damage)
{
    health_ -= damage;
} // decrese_health

//***************************COINPLANT***************************//
CoinPlant::CoinPlant(): Plant(maxHealth_, 0, name_, false), visitLeft_(visitNeed_) {}

void CoinPlant::set_properties(std::string name, int cost, int maxHealth, int visitNeed, int reward)
{
    CoinPlant::name_ = name;
    CoinPlant::cost_ = cost;
    CoinPlant::maxHealth_ = maxHealth;
    CoinPlant::visitNeed_ = visitNeed;
    CoinPlant::reward_ = reward;
} // set_properties

std::string CoinPlant::get_info()
{
    std::string info = name_;
    info += " $" + std::to_string(CoinPlant::cost_);
    info += " HP: " + std::to_string(CoinPlant::maxHealth_);
    info += " - gives $" + std::to_string(CoinPlant::reward_);
    info += " every " + std::to_string(CoinPlant::visitNeed_) + " rounds";
    return info;
} // get_info

std::string CoinPlant::get_state() const
{
    std::string state = name_;
    state += " HP: " + std::to_string(health_);
    state += " (" + std::to_string(visitLeft_);
    state += " more visit";
    if (visitLeft_ < 2)
    {
        state += ")";
    } // if
    else
    {
        state += "s)";
    } // else
    return state;
} // get_state

std::string CoinPlant::attack(Zombie *zombie)
{
    return "";
}

std::string CoinPlant::get_name()
{
    return CoinPlant::name_;
} // get_name

int CoinPlant::get_cost() const
{
    return CoinPlant::cost_;
} // get_cost

void CoinPlant::visit(Player &player, std::vector<Zombie *> zombies, std::vector<Plant *> plants)
{
    std::string action = "";
    visitLeft_ -= 1;
    
    if (visitLeft_ > 0)
    {
        action = "You still need " + std::to_string(visitLeft_) + " visit to earn money.";
    } // if
    else
    {
        player.earn_money(reward_);
        action = "You have earned $" + std::to_string(CoinPlant::reward_) + "! ";
        action += "Now you have $" + std::to_string(player.get_money()) + ".";
        visitLeft_ = 2;
    } // else

    std::cout << action << std::endl;
    system("pause");
} // visit
int CoinPlant::get_maxHealth() const
{
    return CoinPlant::maxHealth_;
}
//***************************HORNPLANT *************************** //
HornPlant::HornPlant(): Plant(maxHealth_, 0, name_, true) {}

void HornPlant::set_properties(std::string name, int cost, int maxHealth, int damage)
{
    HornPlant::name_ = name;
    HornPlant::cost_ = cost;
    HornPlant::maxHealth_ = maxHealth;
    HornPlant::damage_ = damage;
} // set_properties

std::string HornPlant::get_info()
{
    std::string info = HornPlant::name_;
    info += " $" + std::to_string(HornPlant::cost_);
    info += " HP: " + std::to_string(HornPlant::maxHealth_);
    info += " - gives " + std::to_string(HornPlant::damage_);
    info += " damage points";
    return info;
} // get_info

std::string HornPlant::get_state() const
{
    std::string state = HornPlant::name_;
    state += " HP: " + std::to_string(health_);
    return state;
} // get_state

std::string HornPlant::attack(Zombie *zombie)
{
    zombie->decrease_health(damage_);
    return name_ + " gives " + std::to_string(damage_) + " damage to the zombie!";
}

std::string HornPlant::get_name()
{
    return HornPlant::name_;
} // get_name

int HornPlant::get_cost() const
{
    return HornPlant::cost_;
} // get_cost

void HornPlant::visit(Player &player, std::vector<Zombie *> zombies, std::vector<Plant *> plants)
{
    std::string action = "Your " + name_ + " is guarding your land.";
    std::cout << action << std::endl;
    system("pause");
} // visit

int HornPlant::get_maxHealth() const
{
    return HornPlant::maxHealth_;
}
//***************************BOMBPLANT***************************//
BombPlant::BombPlant(): Plant(maxHealth_, 0, name_, true)
{

}//BombPlant::BombPlant

BombPlant::~BombPlant()
{
    ++deadBombCnt_;
}//BombPlant::~BombPlant

void BombPlant::set_properties(std::string name, int cost, int maxHealth, int damage)
{
    BombPlant::name_ = name;
    BombPlant::cost_ = cost;
    BombPlant::maxHealth_ = maxHealth;
    BombPlant::damage_ = damage;
} // set_properties

std::string BombPlant::get_info()
{
    std::string info = BombPlant::name_;
    info += " $" + std::to_string(BombPlant::cost_);
    info += " HP: " + std::to_string(BombPlant::maxHealth_);
    info += " - gives " + std::to_string(BombPlant::damage_);
    info += " damage points";
    return info;
} // get_info

std::string BombPlant::get_state() const
{
    std::string state = BombPlant::name_;
    state += " HP: " + std::to_string(health_);
    return state;
} // get_state

std::string BombPlant::attack(Zombie *zombie)
{
    zombie->decrease_health(damage_);
    health_ = 0;
    return name_ + " gives " + std::to_string(damage_) + " damage to the zombie!";
}

std::string BombPlant::get_name()
{
    return BombPlant::name_;
} // get_name

int BombPlant::get_cost() const
{
    return BombPlant::cost_;
} // get_cost

void BombPlant::visit(Player &player, std::vector<Zombie *> zombies, std::vector<Plant *> plants)
{
    std::string action = "Your " + name_ + " is guarding your land.";
    std::cout << action << std::endl;
    system("pause");
} // visit

int BombPlant::get_dead_bomb_cnt()
{
    return deadBombCnt_;
}//BombPlant::get_dead_bomb_num

int BombPlant::get_maxHealth() const
{
    return BombPlant::maxHealth_;
}
//***************************HEALPLANT***************************//
HealPlant::HealPlant(): Plant(maxHealth_, 0, name_, false) {}

void HealPlant::set_properties(std::string name, int cost, int maxHealth, int healPoints)
{
    HealPlant::name_ = name;
    HealPlant::cost_ = cost;
    HealPlant::maxHealth_ = maxHealth;
    HealPlant::healPoints_ = healPoints;
} // set_properties

std::string HealPlant::get_info()
{
    std::string info = HealPlant::name_;
    info += " $" + std::to_string(HealPlant::cost_);
    info += " HP: " + std::to_string(HealPlant::maxHealth_);
    info += " - gives all your plants " + std::to_string(HealPlant::healPoints_);
    info += " HP back";
    return info;
} // get_info

std::string HealPlant::get_state() const
{
    std::string state = HealPlant::name_;
    state += " HP: " + std::to_string(health_);
    return state;
} // get_state

std::string HealPlant::attack(Zombie *zombie)
{
    return "";
}

std::string HealPlant::get_name()
{
    return HealPlant::name_;
} // get_name

int HealPlant::get_cost() const
{
    return HealPlant::cost_;
} // get_cost

void HealPlant::visit(Player &player, std::vector<Zombie *> zombies, std::vector<Plant *> plants)
{
    std::string action = "";
    for (auto plant : plants)
    {
        plant->increse_health(HealPlant::healPoints_, plant->get_maxHealth());
    }
    action = "All your plants have recovered " + std::to_string(HealPlant::healPoints_) + " HP !\n";
    std::cout << action << std::endl;
    system("pause");
} // visit

int HealPlant::get_maxHealth() const
{
    return HealPlant::maxHealth_;
}
