#include "AnimationCreator.h"

#include "Animation.h"

namespace animation {

Creator::Creator() {
    std::function<Manager(const Creator*)> ptr;
    ptr = &Creator::make_ship;
    _method_map.push_back(ptr);
    ptr = &Creator::make_space;
    _method_map.push_back(ptr);
    ptr = &Creator::make_blackhole;
    _method_map.push_back(ptr);
    ptr = &Creator::make_bullet;
    _method_map.push_back(ptr);
    ptr = &Creator::make_portal;
    _method_map.push_back(ptr);
}

Manager Creator::get_animation(Id id) const {
    return _method_map[static_cast<size_t>(id)](this);
}

Manager Creator::make_ship() const {
    // Исходный размер: 480 128
    Manager ship(_holder.get(Id::SHIP));
    ship.set_switch_time(sf::seconds(0.1f));
    ship.set_image_count(sf::Vector2u(5, 1));
    ship.set_start_angle(90);

    ship.set_size(sf::Vector2f(48, 64));
    ship.set_origin(sf::Vector2f(24, 37));
    return ship;
}

Manager Creator::make_space() const {
    // Исходный размер: 450 450
    Manager space(_holder.get(Id::SPACE));
    space.set_image_count(sf::Vector2u(1, 1));
    space.set_switch_time(sf::seconds(1.f));
    return space;
}

Manager Creator::make_blackhole() const {
    // Исходный размер: 1346 1346
    Manager blackhole(_holder.get(Id::BLACKHOLE));
    blackhole.set_image_count(sf::Vector2u(1, 1));
    blackhole.set_size(sf::Vector2f(250, 250));
    blackhole.set_origin(sf::Vector2f(125, 125));
    return blackhole;
}

Manager Creator::make_bullet() const {
    // Исходный размер 640 160
    Manager bullet(_holder.get(Id::BULLET));
    bullet.set_image_count(sf::Vector2u(4, 1));
    bullet.set_size(sf::Vector2f(30, 30));
    bullet.set_origin(sf::Vector2f(15, 15));
    bullet.set_switch_time(sf::seconds(0.03f));
    return bullet;
}

Manager Creator::make_portal() const {
    // Исходный размер 728 824
    Manager bullet(_holder.get(Id::PORTAL));
    bullet.set_image_count(sf::Vector2u(4, 4));
    bullet.set_size(sf::Vector2f(182, 206));
    bullet.set_origin(sf::Vector2f(75, 85));
    bullet.set_switch_time(sf::seconds(0.3f));
    return bullet;
}

}  // namespace animation
