#include "Player.hpp"
#include "Map.hpp"

int Player::get_money() const
{
    return money_;
}

// int Player::get_position() const
// {
//     return position_;
// }

void Player::earn_money(int reward)
{
    money_ += reward;
}

void Player::buy(const Plant &newPlant)
{
    money_ -= newPlant.get_cost();
    // Map::add_plant(newPlant);
}
