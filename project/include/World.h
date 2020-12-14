#pragma once

#include <queue>
#include <vector>
#include <memory>
#include <list>

#include "Engine.h"
#include "Player.h"
#include "Status.h"
#include "Bullet.h"

class World {
 public:
    World();
    ~World() = default;

    void update(sf::Time d_time);
    std::queue<Player::Action>& get_actions();
    std::vector<std::vector<Status>> get_status();
    // size_t get_player_id();
    bool is_over();

    void push_player(std::unique_ptr<engine::MoveAble> player);
    void push_back(std::unique_ptr<engine::ImmoveAble> immoveable);
    void push_back(std::unique_ptr<engine::MoveAble> moveable);
    void push_back(std::unique_ptr<space::Bullet> bullet);

    void set_player_count(size_t player_count);

 private:
//    std::vector<std::unique_ptr<engine::Entity>> _objects;
    std::queue<Player::Action> _actions;

    std::queue<std::pair<size_t, Player::Action>> _actions_;

    std::vector<std::unique_ptr<engine::MoveAble>> _players;
    std::vector<std::unique_ptr<engine::MoveAble>> _moveable;
    std::vector<std::unique_ptr<space::Bullet>> _bullet;
    std::vector<std::unique_ptr<engine::ImmoveAble>> _immoveable;

    std::vector<std::vector<Status>> _status;

    size_t _player_count;
    size_t _moveable_count;
    size_t _immoveable_count;

    void do_action(size_t id, Player::Action action, sf::Time d_time);
};

// struct ShipMover
// {
//    ShipMover(float vx, float vy)
//    : velocity(vx, vy)
//    {
//    }

//    void operator() (space::Ship& ship, sf::Time) const
//    {
//        ship.get_acceleration()
//    }

//    sf::Vector2f velocity;
// };
