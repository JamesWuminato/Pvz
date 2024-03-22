#include "Zombie.hpp"
#include "Plant.hpp"
#include <iostream>
#include <string>
int Zombie::get_position()const
{
    return position_;
}
int Zombie::get_id()const
{
    return id_;
}
int Zombie::get_health()const
{
    return Health_;   
}
void Zombie::decrease_health(const int damage)
{
    Health_ -= damage;
}
void Zombie::move(int newPosition)
{
    position_ = newPosition;
}
std::string Zombie::get_stats() const
{
    std::string id = std::to_string(id_), hp = std::to_string(Health_); //[id] Damage: 15 HP:******************************
    std::string stats = "[" + id + "]" + " Damage: 15 HP:";
    for(int i = 0; i < Health_; ++i)
    {
        stats += "*";
    }
    return stats;
}
void Zombie::attack(Plant *plant)
{
    std::string name = plant->get_type_name();
    plant->decrease_health(damage);
    std::cout << "Zombie eats plant " << name << " and causes damage 15." << std::endl;
}
