#pragma once
#include <SFML/Network/TcpSocket.hpp>
#include "GameManager.h"

class Network
{
public:
    Network(sf::IpAddress&, uint16_t);
    void Diconnect(const std::shared_ptr<GameManager>&);
    void SendMove(const std::shared_ptr<GameManager>&);
    void SendBoxes(const std::shared_ptr<GameManager>&);
    void Receive(const std::shared_ptr<GameManager>&);

private:
    sf::TcpSocket m_socket;
    bool m_connected;
};
