#ifndef LAND_HPP
#define LAND_HPP

#include <vector>

class Zombie;
class Plant;

class Land
{
public:
    Land(){};
    ~Land();
    void display(const int landId, const int numZombies) const;
    std::vector<Zombie*> get_zombies()const;
    Plant* get_plant()const;
    bool has_plant()const;
    bool has_player()const;
    bool has_zombie()const;
    void add_plant(Plant *plant);
    void add_zombie(Zombie *zombie);
    void remove_dead_plant();
    void remove_dead_zombies();
private:
    bool hasPlayer_ = false;
    Plant* plant_ = nullptr;
    std::vector<Zombie*> zombies_;

    friend class Map;
};

#endif
