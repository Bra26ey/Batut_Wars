#include "IcePlanet.h"

namespace space {

IcePlanet::IcePlanet(float range) : space::Planet(range) {}

void IcePlanet::collision(space::Bullet& bullet) {
  float critical_radius = _range + 12;

  engine::Vector radius;

  if (bullet.get_x() > get_x()) {
    radius = engine::Vector(bullet.get_x() - get_x(), bullet.get_y() - get_y());
  } else {
    radius = engine::Vector(-bullet.get_x() + get_x(), -bullet.get_y() + get_y());
  }

  if (radius.get_abs() >= critical_radius) {
    return;
  }

  float angle = radius.compute_angle(bullet.get_orientation());  // rad

  bullet.rotate(angle * 2);
}  // протестировать не могём
   // могете

animation::Id IcePlanet::get_animation_id() const {
  return animation::Id::ICE_PLANET;
}

void IcePlanet::trigger(engine::MoveAble &) {}

void IcePlanet::update(sf::Time) {}

}  // namespace space