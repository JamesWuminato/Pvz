#include <iostream>
#include <vector>

#include "Game.hpp"
#include "Plant.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Land.hpp"
#include "Zombie.hpp"

int main()
{
    CoinPlant coinPlant;
    HornPlant hornPlant;
    BombPlant bombPlant;
    HealPlant HealFlower;

    Game game(coinPlant,hornPlant,bombPlant,HealFlower);
    game.start(coinPlant,hornPlant,bombPlant,HealFlower);

    return 0;
} // main
