#include "Map.hpp"
#include "Zombie.hpp"
#include "Plant.hpp"
#include "Land.hpp"

Map::Map(const int landNum, const int position): lands_(std::vector<Land>(landNum)), playerPosition_(position) {}

void Map::display(const int numZombies) const
{
    for(size_t i = 0; i < lands_.size(); ++i)
    {
        lands_[i].display(i, numZombies);
    }
}

void Map::move_player_to(int newPosition)
{
    lands_[playerPosition_].hasPlayer_ = false;
    playerPosition_ = newPosition;
    lands_[playerPosition_].hasPlayer_ = true;
}

void Map::move_zombie_to(int id, int newPosition)
{
    for (Land &l : lands_)
    {
        for (size_t i = 0; i < l.zombies_.size(); ++i)
        {
            if (l.zombies_[i]->get_id() == id)
            {
                l.zombies_[i]->move(newPosition);
                lands_[newPosition].add_zombie(l.zombies_[i]);
                l.zombies_.erase(l.zombies_.begin() + i);
                return;
            }//if
        }//for z
    }//for l
}

int Map::get_player_position()const
{
    return this->playerPosition_;
}
std::vector<Zombie*> Map::get_all_zombies() const
{
    std::vector<Zombie*> all_zombies;
    for(size_t i = 0; i < lands_.size(); ++i)
    {
        std::vector<Zombie*> zombies = lands_[i].get_zombies();
        all_zombies.insert(all_zombies.end(), zombies.begin(), zombies.end());
    }
    return all_zombies;
}
std::vector<Plant*> Map::get_all_plants()
{
    std::vector<Plant*> all_plants;
    for(size_t i = 0; i < lands_.size(); ++i)
    {
        Plant *plant = lands_[i].get_plant();
        if (plant != nullptr)
            all_plants.push_back(plant);
    }
    return all_plants;
}

Plant* Map::get_plant_on(int landId)
{
    return lands_[landId].plant_;
}//Map::get_plant_on

void Map::add_plant(Plant *plant)
{
    lands_[playerPosition_].add_plant(plant);
}
void Map::add_zombie(Zombie *zombie)
{
    lands_[zombie->get_position()].add_zombie(zombie);
}

void Map::remove_dead_plants()
{
    for (Land &l : lands_)
    {
        l.remove_dead_plant();
    }//for l
}

void Map::remove_dead_zombies()
{
    for (Land &l : lands_)
    {
        l.remove_dead_zombies();
    }//for l
}
