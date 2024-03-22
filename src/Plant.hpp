#ifndef PLANT_HPP
#define PLANT_HPP

#include <string>
#include <vector>
#include "Zombie.hpp"
#include "Player.hpp"
class Zombie;
class Player;

class Plant
{
public:
    Plant(){};
    Plant(int health, int position = 0, std::string typeName = "", bool isOffensive = false);
    virtual ~Plant(){};
    int get_position() const;
    int get_health() const;
    bool is_offensive() const;
    const std::string& get_type_name() const;
    void move_to(int position);
    void increse_health(int heal_points, int maxHealth);
    void decrease_health(int damage);
    virtual std::string get_state() const = 0;
    virtual std::string attack(Zombie *Zombie) = 0;
    virtual int get_cost() const = 0;
    virtual int get_maxHealth() const = 0;
    virtual void visit(Player &player, std::vector<Zombie *> zombies, std::vector<Plant *> plants) = 0;

protected:
    int health_ = 0;
    int position_ = 0;
    std::string typeName_ = "";
    bool isOffensive_ = false;
};

class CoinPlant : public Plant
{
public:
    CoinPlant();

    static void set_properties(std::string name, int cost, int maxHealth, int visitNeed, int reward);
    static std::string get_info();
    virtual std::string get_state() const override;
    virtual std::string attack(Zombie *zombie) override;
    static std::string get_name();
    virtual int get_maxHealth() const override;
    int get_cost() const override;
    void visit(Player &player, std::vector<Zombie *> zombies, std::vector<Plant *> plants) override;

private:
    int visitLeft_ = 0;
    static std::string name_;
    static int cost_;
    static int reward_;
    static int visitNeed_;
    static int maxHealth_;
};

class HornPlant : public Plant
{
public:
    HornPlant();
    static void set_properties(std::string name, int cost, int maxHealth, int damage);
    static std::string get_info();
    virtual std::string get_state() const override;
    virtual std::string attack(Zombie *zombie) override;
    static std::string get_name();
    virtual int get_maxHealth() const override;
    int get_cost() const override;
    void visit(Player &player, std::vector<Zombie *> zombies, std::vector<Plant *> plants) override;

private:
    static std::string name_;
    static int cost_;
    static int maxHealth_;
    static int damage_;
};

class BombPlant : public Plant
{
public:
    BombPlant();
    ~BombPlant();
    static void set_properties(std::string name, int cost, int maxHealth, int damage);
    static std::string get_info();
    virtual std::string get_state() const override;
    virtual std::string attack(Zombie *zombie) override;
    static std::string get_name();
    virtual int get_maxHealth() const override;
    int get_cost() const override;
    void visit(Player &player, std::vector<Zombie *> zombies, std::vector<Plant *> plants) override;
    static int get_dead_bomb_cnt();

private:
    static std::string name_;
    static int cost_;
    static int maxHealth_;
    static int damage_;
    static int deadBombCnt_;
};

class HealPlant : public Plant
{
public:
    HealPlant();
    static void set_properties(std::string name, int cost, int maxHealth, int healPoints);
    static std::string get_info();
    virtual std::string get_state() const override;
    virtual std::string attack(Zombie *zombie) override;
    static std::string get_name();
    virtual int get_maxHealth() const override;
    int get_cost() const override;
    void visit(Player &player, std::vector<Zombie *> zombies, std::vector<Plant *> plants) override;

private:
    static std::string name_;
    static int cost_;
    static int maxHealth_;
    static int healPoints_;
};

#endif
