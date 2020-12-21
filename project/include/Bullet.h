#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include "Engine.h"

namespace space {
class Bullet : public engine::MoveAble {
 public:
  Bullet();
  ~Bullet() = default;
  int get_damage() const;
  void collision(engine::MoveAble &object);
  animation::Id get_animation_id() const override;

  void update(sf::Time dt) override;

 private:
  sf::Vector2f _bounds;
  int _dmg;

  const sf::Time _lifetime;
  sf::Time _current;
};

}  // namespace space