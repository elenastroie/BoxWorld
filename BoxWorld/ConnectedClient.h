#pragma once
#include <SFML/Network/TcpSocket.hpp>
#include <memory>

class ConnectedClient
{

public:
    explicit ConnectedClient(std::shared_ptr<sf::TcpSocket>&);
    [[nodiscard]] uint8_t GetId() const;
    [[nodiscard]] std::shared_ptr<sf::TcpSocket> GetSocket() const;
    void SetTimeout(sf::Time time);
    [[nodiscard]] sf::Time GetTimeout() const;
    bool operator==(const ConnectedClient&) const;
    bool operator!=(const ConnectedClient&) const;

private:
    uint8_t m_id;
    std::shared_ptr<sf::TcpSocket> m_socket;
    static uint8_t s_numberOfConnectedClients;
    sf::Time m_timeout;
};

