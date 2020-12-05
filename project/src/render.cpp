#include "render.h"

#include <vector>

Render::Render(sf::RenderWindow& window)
    : _window(window) {
    _animation_layers.resize(static_cast<size_t>(animation::LayerNom::COUNT));

    const sf::Texture *space = _holder.get_texture(animation::Id::SPACE);
    size_t width = space->getSize().x;
    size_t height = space->getSize().y;
    for (size_t i = 0; i <= 1280 / width; ++i) {  //
        for (size_t j = 0; j <= 960 / height; ++j) {
            animation::AnimationManager added(space, sf::Vector2f(i * width, j * height), 0);
            _animation_layers[0].push_back(added);
        }
    }

    _view.setSize(640, 480);
}

void Render::draw() {
    for (auto &it : _animation_layers) {
        it.draw(_window);
    }
}

void Render::update(sf::Time dt) {
    _view.setCenter(_status[0].position);
    for (auto &it : _animation_layers) {
        it.update(dt);
    }
}

void Render::inicilize(const std::vector<Status> &status) {
    _status.assign(status.begin(), status.end());
    _view.setCenter(_status[0].position);  // TODO(ANDY) вместо 0 - id данного игрока
    build_scene();
}

void Render::build_scene() {
    for (auto &it : _status) {
        animation::AnimationManager added(_holder.get_texture(it.animation_id), it.position, it.angle);
        _animation_layers[it.lay_id].push_back(added);
    }
}

void Render::set_status(const std::vector<Status> &status) {
    for (size_t i = 0; i < _status.size(); ++i) {  // TODO(ANDY) Ломается при удалении. Переписать на list
        size_t lay = status[i].lay_id;
        size_t id = status[i].id;
        if (status[i].is_removed) {
            _status.erase(status.begin() + i);
            _animation_layers[lay].erase(id);
            continue;
        }

        if (_status[i].states != status[i].states) {
            _status[i].states = status[i].states;
            _animation_layers[lay][id].set_states(_status[i].states);
        }

        _status[i].angle = status[i].angle;
        _animation_layers[lay][id].set_angle(status[i].angle);

        _status[i].position = status[i].position;
        _animation_layers[lay][id].set_position(status[i].position);
    }

    for (size_t i = _status.size(); i < status.size(); ++i) {
        _status.push_back(status[i]);
    }
}

void Render::add_animation(size_t lay, Status &status) {
    animation::AnimationManager added(_holder.get_texture(status.animation_id), status.position, status.angle);
    _animation_layers[lay].push_back(added);
}

sf::View& Render::get_view() {
    return _view;
}
