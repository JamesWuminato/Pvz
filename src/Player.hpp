#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Plant.hpp"
class Plant;
class Player
{
public:
    int get_money() const;
    // int get_position() const;
    void earn_money(int reward);
    void buy(const Plant &newPlant);

protected:
    int money_ = 0;
    // int position_ = 0;
};

#endif