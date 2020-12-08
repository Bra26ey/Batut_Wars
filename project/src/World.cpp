#include "World.h"

#include <cassert>
#include <memory>
#include <algorithm>

#include "Ship.h"
#include "Layer.h"
#include "Engine.h"

static const size_t MAP_SIZE = 2000;  // Криво, но пока надо

static Status to_status(engine::Entity const &entity) {
    Status status;
    status.id = entity.get_id();
    status.is_removed = false;  // TODO(ANDY) в зависимости от hp
    status.animation_id = entity.get_animation_id();
    status.lay_id = static_cast<size_t>(animation::LayerNom::OBJECTS);  // TODO(ANDY) получить LayerNom по Id
    status.states = entity.get_state();
    status.angle = 0;  // TODO(ANDY) костыль
    status.position = entity.get_position();
    return status;
}

World::World() {}  // TODO(ANDY) написать нормальный конструктор

void World::update(sf::Time d_time) {
    while (!_actions.empty()) {
        do_action(0, _actions.front(), d_time);
        _actions.pop();
    }

    for (size_t i = 0; i < _objects.size(); ++i) {
        _objects[i]->update(d_time);
        _status[i].position = _objects[i]->get_position();  // TODO(ANDY) обновление status (после реализации angle в Entity)

        if (_status[i].position.x > MAP_SIZE) {
            _status[i].position.x -= MAP_SIZE;
            _objects[i]->set_x(_status[i].position.x);
        }
        if (_status[i].position.x < 0) {
            _status[i].position.x += MAP_SIZE;
            _objects[i]->set_x(_status[i].position.x);
        }
        if (_status[i].position.y > MAP_SIZE) {
            _status[i].position.y -= MAP_SIZE;
            _objects[i]->set_y(_status[i].position.y);
        }
        if (_status[i].position.y < 0) {
            _status[i].position.y += MAP_SIZE;
            _objects[i]->set_y(_status[i].position.y);
        }
    }
    // Рассчет коллизий
}

bool World::is_over() {
    return true;  // TODO(ANDY) убрать заглушку
}

void World::push_back(std::unique_ptr<engine::Entity> object) {
    _objects.push_back(std::move(object));
    Status status = to_status(dynamic_cast<engine::Entity&>(*_objects.back()));
    _status.push_back(status);
}

void World::do_action(size_t id, Player::Action action, sf::Time d_time) {  // TODO(ANDY) переписать на таблицу Command
    // auto it = std::find_if(_objects.begin(), _objects.end(),
    //                [] (std::unique_ptr<engine::Entity> &it) { 
    //                     return it->get_id();
    //                 });

    // auto &ship = dynamic_cast<space::Ship&>(**it);

    auto &ship = dynamic_cast<space::Ship&>(*_objects[id]);

    switch (action) {
    case Player::Action::MOVE_FORWARD:
        ship.give_acceleration(Direction::FORWARD, 10.0 * d_time.asSeconds());  // TODO(ANDY) довести до ума
        break;
    case Player::Action::MOVE_BACKWARD:
        ship.give_acceleration(Direction::BACKWARD, 10.0 * d_time.asSeconds());  // TODO(ANDY) довести до ума
        break;
    case Player::Action::MOVE_LEFT:
        ship.rotate(engine::to_radian(- 60.0) * d_time.asSeconds());  // TODO(ANDY) довести до ума
        _status[id].angle -= 60.0 * d_time.asSeconds();
        break;
    case Player::Action::MOVE_RIGHT:
        ship.rotate(engine::to_radian(60.0) * d_time.asSeconds());  // TODO(ANDY) довести до ума блять
        _status[id].angle += 60.0 * d_time.asSeconds();
        break;

    default:
        break;
    }
}

std::vector<Status> World::get_status() {
    return _status;
}

std::queue<Player::Action>& World::get_actions() {
    return _actions;
}
