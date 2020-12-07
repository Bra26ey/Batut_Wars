#include "GameState.h"

#include "Ship.h"

GameState::GameState(StateStack& stack, Context context)
          : State(stack, context),
          _world(),
          _render(*context.window),
          _Player(*context.player),
          _frames(0) {

    _statistic_font.loadFromFile("project/media/Sansation.ttf");
    _statistic_text.setFont(_statistic_font);
    _statistic_text.setPosition(5.f, 5.f);
    _statistic_text.setCharacterSize(10);

    space::Ship *main_ship = new space::Ship;  // TODO(ANDY) инициализация карты
    main_ship->set_position(sf::Vector2f(1000, 1000));
    _world.push_back(*main_ship);
    // space::Ship other_ship;  // тупой бот
    // other_ship.set_position(sf::Vector2f(1100, 1000));
    // _world.push_back(other_ship);
    _render.inicilize(_world.get_status());
}

void GameState::draw() {
    _render.draw();
}

bool GameState::update(sf::Time dt) {
    _world.update(dt);
    _render.set_status(_world.get_status());  // Обмен данными между _render и _world
    _render.update(dt);

    sf::Vector2f fps = _render.get_view().getCenter();
    fps.x -= _render.get_view().getSize().x / 2 - 5;
    fps.y -= _render.get_view().getSize().y / 2 - 5;
    _statistic_text.setPosition(fps);
    getContext().window->draw(_statistic_text);

    std::queue<Player::Action> &actions = _world.get_actions();
    _Player.handle_realtime_event(actions);
    return true;
}   

bool GameState::handleEvent(const sf::Event& event) {
    std::queue<Player::Action> &actions = _world.get_actions();
    _Player.handle_event(event, actions);

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        requestStackPush(States::Pause);
    }

    return true;
}

void GameState::update_statistic(sf::Time time) {
    _update_time += time;
    _frames += 1;

    if (_update_time >= sf::seconds(1.0f)) {
        _statistic_text.setString(
            "Frames / Second = " + std::to_string(_frames) + "\n" +
            "Time / Update = " + std::to_string(_update_time.asMicroseconds() / _frames) + "us");

        _update_time -= sf::seconds(1.0f);
        _frames = 0;
    }
}
