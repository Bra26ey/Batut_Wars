#pragma once

#include <SFML/Window/Event.hpp>
#include <map>
#include <queue>

enum class Action {
  MOVE_LEFT = 0,
  MOVE_RIGHT,
  MOVE_FORWARD,
  MOVE_BACKWARD,
  COUNT
};

class Player {
 public:
  Player();
  void handle_event(const sf::Event &event, std::queue<Action> &actions);
  void handle_realtime_event(std::queue<Action> &commands);
  void assign_key(Action action, sf::Keyboard::Key key);
  sf::Keyboard::Key get_key(Action action) const;
  // Action send_action();

 private:
  static bool is_realtime(Action action);

  std::map<sf::Keyboard::Key, Action> _key_binding;
};
