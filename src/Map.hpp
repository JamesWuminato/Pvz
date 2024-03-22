#ifndef MAP_HPP
#define MAP_HPP
#include<vector>
#include "Land.hpp"
class Zombie;
class Plant;
class Land;

class Map
{
public:
    Map(){};
    Map(const int landNum,const int position);
    void display(const int numZombies) const;
    void move_player_to(const int newPosition);
    void move_zombie_to(const int id, const int newPosition);
    int get_player_position() const;
    std::vector<Zombie*> get_all_zombies() const;
    std::vector<Plant*> get_all_plants();
    Plant* get_plant_on(int landId);
    void add_plant(Plant *plant);
    void add_zombie(Zombie *zombie);
    void remove_dead_plants();
    void remove_dead_zombies();
private:
    std::vector<Land> lands_;
    int playerPosition_ = 0;
};

#endif
