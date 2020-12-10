#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Network.hpp>

#include "World.h"

namespace network {

constexpr int START = 1;

class Server {
 public:
    Server();
    ~Server();
    void run();
    std::pair<sf::IpAddress, uint16_t> get_adress() const;

 private:
    World _world;
    sf::Time _time_per_update;

    std::vector<sf::TcpSocket*> _clients;
    sf::SocketSelector _selector;
    sf::TcpListener _listener;
    sf::IpAddress _ip;
    uint16_t _port;
    size_t _host;

    void accept_clients();
    void get_client_actions();
    void send_update();
    void add_client();
    bool is_started();
};

}  // namespace network
