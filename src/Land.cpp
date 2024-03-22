#include "Land.hpp"
#include "Zombie.hpp"
#include "Plant.hpp"
#include <iostream>
#include <string>
#include <algorithm>

Land::~Land()
{
    delete plant_;

    for (Zombie *z : zombies_)
    {
        delete z;
    }//for z
    zombies_.clear();
}
void Land::display(const int landId, const int numZombies) const
{
    std::string land = "[" + std::to_string(landId) + "]{";

    //player
    if(hasPlayer_)
    {
        land += "*";
    }//if
    else
    {
        land += " ";
    }//else

    //zombies
    
    for(int i = 0, cnt = 0; i < numZombies; ++i)
    {
        bool hasZombie = false;
        for (size_t j = cnt; j < zombies_.size(); ++j)
        {
            if (zombies_[j]->get_id() == i)
            {
                land += std::to_string(zombies_[j]->get_id());
                hasZombie = true;
                ++cnt;
                break;
            }//if
        }//for j

        if (!hasZombie)
        {
            land += " ";
        }//if
    }//for i

    land += "}";
    
    //plant
    if(plant_ != nullptr)
    {
        land += plant_->get_state();
    }
    else
    {
        land += "Empty";
    }
    std::cout << land << std::endl;
}
std::vector<Zombie*> Land::get_zombies()const
{
    return zombies_;
}
Plant* Land::get_plant()const
{
    return plant_;
}
bool Land::has_plant()const
{
    return plant_ != nullptr;
}
bool Land::has_player()const
{
    return hasPlayer_;
}
bool Land::has_zombie()const
{
    return zombies_.empty();
}
void Land::add_plant(Plant *plant)
{
    if(plant_ == nullptr)
    {
        plant_ = plant;
    }
}
void Land::add_zombie(Zombie *zombie)
{
    zombies_.push_back(zombie);
    std::sort(zombies_.begin(), zombies_.end(), [](Zombie *a, Zombie *b) { return (a->get_id()) < (b->get_id()); });
}
void Land::remove_dead_plant()
{
    if (plant_ == nullptr) return;

    if (plant_->get_health() <= 0)
    {
        delete plant_;
        plant_ = nullptr;
    }//if
}
void Land::remove_dead_zombies()
{
    for (size_t i = 0; i < zombies_.size(); ++i)
    {
        if (zombies_[i]->get_health() <= 0)
        {
            delete zombies_[i];
            zombies_.erase(zombies_.begin() + i);
            --i;
        }//if
    }//for it
}
