#ifndef Game_HPP
#define Game_HPP
#include <iostream>
#include "Plant.hpp"
#include "Map.hpp"
class Player;
class Zombie;
class Plant;
class Map;
class Land;
class Game
{
public:
    Game(CoinPlant& coinPlant,HornPlant& hornplant,BombPlant& bombplant,HealPlant& Healflower)
    {
        std::string file_name = "plants.txt" ;
        read_txt(file_name,coinPlant,hornplant,bombplant,Healflower);
        read_game_settings();
    };

    void start(CoinPlant &coinPlant,HornPlant &hornPlant,BombPlant &bombPlant,HealPlant &healPlant);

private:
    Map map_;
    Player player_;
    int numLands_ = 0;
    int numZombies_ = 0;
    int lastChoice_ = 4;
    bool gameEnd_= 0;
    bool winned_ = false;
    bool bombUsed_ = false;
    void read_txt(const std::string &fileName,CoinPlant &coinPlant,HornPlant &hornPlant,BombPlant &bombPlant,HealPlant &healPlant);
    void read_game_settings();
    void move_player();
    void move_zombies();
    void display() const;
    void round();
};

#endif
