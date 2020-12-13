#include "Game.h"

#include <string>
#include <utility>

#include "StateIdentifiers.h"
#include "TitleState.h"
#include "MenuState.h"
#include "OnlineMenuState.h"
#include "GameState.h"
#include "SettingState.h"
#include "GameState.h"
#include "PauseState.h"
#include "OnlineState.h"

const sf::Time Game::_time_per_frame = sf::seconds(1.0 / 60.0);

Game::Game() : _window(sf::VideoMode(640, 480), "Batut Wars", sf::Style::Close),
               _player(),
               _textures(),
               _fonts(),
               _network_info(),
               _client(),
               _server(),
               _server_thread(),
               _state_stack(State::Context(_window, _textures, _fonts, _player, _network_info, _client, _server, _server_thread)) {
    _window.setKeyRepeatEnabled(false);
    _window.setVerticalSyncEnabled(true);
    registrates();
    _state_stack.push(States::Id::TITLE);
}


void Game::run() {
    sf::Clock clock;
    sf::Time total_time = sf::Time::Zero;

    while (_window.isOpen()) {
        sf::Time current_time = clock.restart();
        total_time += current_time;

        while (total_time > _time_per_frame) {
            total_time -= _time_per_frame;

            get_input();
            update(_time_per_frame);

            if (_state_stack.is_empty()) {
                _window.close();
            }
        }

        render();
    }
}

bool Game::update(sf::Time dt) {
    _state_stack.update(dt);
    return true;
}

void Game::render() {
    _window.clear();
    _state_stack.draw();
    // _window.setView(_window.getDefaultView());  // Вид устанавливается в _render.set_status
    _window.display();
}

void Game::get_input() {
    sf::Event event;

    while (_window.pollEvent(event)) {
        _state_stack.handle_event(event);

        if (event.type == sf::Event::Closed) {
            _window.close();
        }
    }
}

void Game::registrates() {
    _state_stack.registrate<TitleState>(States::TITLE);
    _state_stack.registrate<MenuState>(States::MENU);
    _state_stack.registrate<OnlineMenuState>(States::ONLINE_MENU);
    _state_stack.registrate<GameState>(States::GAME);
    _state_stack.registrate<OnlineState>(States::ONLINE);
    _state_stack.registrate<PauseState>(States::PAUSE);
    _state_stack.registrate<SettingsState>(States::SETTINGS);
}
