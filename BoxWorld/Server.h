#pragma once
#pragma once
#include <iostream>
#include <SFML/Network.hpp>
#include <memory>
#include <vector>
#include <string>
#include "ConnectedClient.h"

class Server
{
public:
    Server();
    void Run();

private:
    void SendMove(sf::Packet& packet, uint8_t skip = -1);
    void SendBoxes(sf::Packet& packet, uint8_t skip = -1);
    void SendDisconnect(int8_t);

private:
    bool m_isRunning;
    sf::IpAddress m_ipAdress;
    uint32_t m_port;
    sf::TcpListener m_listener;
    sf::SocketSelector m_selector;
    uint8_t m_maxPlayerNumber;
    uint8_t m_currentId;
    uint8_t m_playerNumber;
    std::vector<ConnectedClient> m_connectedClients;
    sf::Clock m_clock;
};

