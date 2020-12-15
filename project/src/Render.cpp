#include "Render.h"

#include <vector>

static constexpr size_t MAP_SIZE = 4 * 450;  // Криво, но пока надо. 450 - размер текстурки космоса

Render::Render(sf::RenderWindow& window)
    : _window(window) {
    _view.setSize(640, 480);

    _animation_layers.resize(static_cast<size_t>(animation::LayerNom::COUNT));
    auto space = _creator.get_animation(animation::Id::SPACE);
    space.set_position(sf::Vector2f(0, 0));
    space.set_angle(0);
    size_t width = space.get_size().x;
    size_t height = space.get_size().y;
    // _extra_size.x = _view.getSize().x / 2;
    // _extra_size.y = _view.getSize().y / 2;
    _extra_size = sf::Vector2f(450, 450);
    size_t x_count = ((MAP_SIZE + _extra_size.x) / width + 1) * 2;
    size_t y_count = ((MAP_SIZE + _extra_size.y) / height + 1) * 2;

    auto portal = _creator.get_animation(animation::Id::PORTAL);
    portal.set_position(sf::Vector2f(0, 0));
    portal.set_angle(0);

    for (size_t i = 0; i <= 3 * 4; ++i) {  // TODO(ANDY) размерность карты
            portal.set_position(sf::Vector2f(i * width / 3, 0) + _extra_size);
            _animation_layers[static_cast<size_t>(animation::LayerNom::EFFECTS)].push_back(portal);
    }
    for (size_t i = 0; i <= 3 * 4; ++i) {  // TODO(ANDY) размерность карты
            portal.set_position(sf::Vector2f(i * width / 3, 4 * 450) + _extra_size);
            _animation_layers[static_cast<size_t>(animation::LayerNom::EFFECTS)].push_back(portal);
    }
    for (size_t i = 0; i <= 3 * 4; ++i) {  // TODO(ANDY) размерность карты
            portal.set_position(sf::Vector2f(0, i * height / 3) + _extra_size);
            _animation_layers[static_cast<size_t>(animation::LayerNom::EFFECTS)].push_back(portal);
    }
    for (size_t i = 0; i <= 3 * 4; ++i) {  // TODO(ANDY) размерность карты
            portal.set_position(sf::Vector2f(4 * 450, i * height / 3) + _extra_size);
            _animation_layers[static_cast<size_t>(animation::LayerNom::EFFECTS)].push_back(portal);
    }

    for (size_t i = 0; i <= x_count; ++i) {  // TODO(ANDY) размерность карты
        for (size_t j = 0; j <= y_count; ++j) {
            space.set_position(sf::Vector2f(i * width, j * height));
            _animation_layers[static_cast<size_t>(animation::LayerNom::BACKGROUND)].push_back(space);
        }
    }
}

void Render::draw() {
    for (auto &it : _animation_layers) {
        it.draw(_window);
    }
}

void Render::update(sf::Time dt) {
    _view.setCenter(_status[0][_player_id].position);  // TODO(ANDY) PLAYER = 0
    _window.setView(_view);
    for (auto &it : _animation_layers) {
        it.update(dt);
    }
}

void Render::inicilize(const std::vector<std::vector<Status>> &status) {
    _status.assign(status.begin(), status.end());
    for (auto &lay : _status) {
        for (auto &it : lay) {
            it.position += _extra_size;
        }
    }
    _view.setCenter(_status[0][_player_id].position);
    build_scene();
}

void Render::build_scene() {
    for (auto &lay : _status) {
        for (auto &object : lay) {
            animation::Manager added = _creator.get_animation(object.animation_id);
            _animation_layers[object.lay_id].push_back(added);
        }
    }
}

void Render::set_status(const std::vector<std::vector<Status>> &status) {
    for (size_t i = 0; i < _status.size(); ++i) {  // Мб тупо заменить на inicilize
        for (size_t j = 0; j < _status[i].size(); ++j) {
            size_t lay = status[i][j].lay_id;
            size_t id = status[i][j].id;
            if (status[i][j].is_removed) {
                // _status.erase(status.begin() + i);  // TODO(ANDY)
                // _animation_layers[lay].erase(id);
                 continue;
            }

            _status[i][j].states = status[i][j].states;
            _animation_layers[lay][id].set_states(_status[i][j].states);

            _status[i][j].angle = status[i][j].angle;
            _animation_layers[lay][id].set_angle(status[i][j].angle);

            _status[i][j].position = status[i][j].position + _extra_size;
            _animation_layers[lay][id].set_position(_status[i][j].position);
        }

        for (size_t j = _status[i].size(); j < status[i].size(); ++j) {
            _status[i].push_back(status[i][j]);
            _status[i][j].position += _extra_size;
            add_animation(_status[i][j].lay_id, _status[i][j]);
        }
    }
}

void Render::add_animation(size_t lay, Status &status) {  // lay не нужен
    animation::Manager added = _creator.get_animation(status.animation_id);
    added.set_position(status.position);
    added.set_angle(status.angle);
    _animation_layers[lay].push_back(added);
}

sf::View& Render::get_view() {
    return _view;
}

void Render::set_player_id(size_t id) {
    _player_id = id;
}
