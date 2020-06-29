#include "stdafx.h"
#include "ConnectedClient.h"
#include <SFML/Network/TcpSocket.hpp>

uint8_t ConnectedClient::s_numberOfConnectedClients = 0;


ConnectedClient::ConnectedClient(std::shared_ptr<sf::TcpSocket>& socket)
{
    m_socket = socket;
    m_id = s_numberOfConnectedClients;
    ++s_numberOfConnectedClients;
}

uint8_t ConnectedClient::GetId() const
{
    return m_id;
}

std::shared_ptr<sf::TcpSocket> ConnectedClient::GetSocket() const
{
    return m_socket;
}

void ConnectedClient::SetTimeout(const sf::Time time)
{
    m_timeout = time;
}

sf::Time ConnectedClient::GetTimeout() const
{
    return m_timeout;
}

bool ConnectedClient::operator==(const ConnectedClient& other) const
{
    return m_id == other.m_id;
}

bool ConnectedClient::operator!=(const ConnectedClient& other) const
{
    return m_id != other.m_id;
}
