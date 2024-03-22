#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP
#include <string>
class Plant;

class Zombie
{
public:
    static constexpr int damage = 15;
    static constexpr int maxHealth = 40;
    Zombie() = default;
    Zombie(const int id, const int position): id_(id), position_(position){};
    int get_position()const;
    int get_id()const;
    int get_health()const;
    void decrease_health(const int damage);
    void move(int newPosition);
    std::string get_stats() const;
    void attack(Plant *plant);
private:
    int Health_ = maxHealth;
    int id_ = 0;
    int position_ = 0;
};

#endif
