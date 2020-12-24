#include "Comet.h"
#include <iostream>

namespace space {

Comet::Comet(engine::Vector speed) : engine::MoveAble(0.f, 40) {  // TODO(anyone) переписать конструктор на
  _engine_speed = speed;                                              // модуль скорости + угол (с осью ОХ)
  _orientation = _engine_speed.get_normal();
}

void Comet::collision(engine::MoveAble& moveable) {
  if(!is_destroyed()) {
    float critical_radius = 20;
    engine::Vector tmp(moveable.get_x() - this->get_x(),
                      moveable.get_y() - this->get_y());

    float radius = tmp.get_abs();
    if (radius <= critical_radius) {
      moveable.take_damage(this->_dmg);
      this->take_damage(this->_HP);
      std::cout << moveable.get_hp() << " - Comet - " << this->get_hp()<< std::endl;
    }
  }
}

animation::Id Comet::get_animation_id() const {
  return animation::Id::COMET;
}

void Comet::trigger(engine::MoveAble &) {}

void Comet::update(sf::Time dt) {
  _dictated_speed += _dictated_acceleration * dt.asSeconds();

  if (_dictated_speed.get_abs() > 0) {
    _dictated_speed *= (1 - dt.asSeconds());
  } else {
    _dictated_speed = engine::Vector(0, 0);
  }

  engine::Vector total_speed = _engine_speed + _dictated_speed;

  engine::Vector tmp = total_speed * dt.asSeconds();
  _position += tmp.get_sf();
  _dictated_acceleration.set_x(0);
  _dictated_acceleration.set_y(0);
}

}  // namespace space
   // красава :)   Вообще-то это Антон мне(Лизе) написал :(
   // спасибо (:
   // выходи за меня :)
   // я согласен
