#include "stdafx.h"
#include "Server.h"
#include "Status.h"

Server::Server()
{
    m_maxPlayerNumber = 2;
    m_currentId = 0;
    m_playerNumber = 0;
    m_isRunning = true;
    m_listener.setBlocking(false);
    m_port = 51850;
    m_listener.listen(m_port);
    m_selector.add(m_listener);
    std::cout << m_listener.getLocalPort() << std::endl;
    std::cout << "Server started. Waiting for clients" << std::endl;
}

void Server::Run()
{
    while (m_isRunning)
    {
        if (m_selector.wait())
        {
            if (m_selector.isReady(m_listener)) // if server is ready to receive new connections
            {
                std::shared_ptr<sf::TcpSocket> tempSocket = std::make_shared<sf::TcpSocket>();
                tempSocket->setBlocking(false);

                if (m_listener.accept(*tempSocket) == sf::Socket::Done)
                {
                    if (m_playerNumber < m_maxPlayerNumber) //if server is not full
                    {
                        sf::Packet outPacket;
                        int8_t remoteId;
                        ++m_playerNumber;
                        if (m_playerNumber == 1)
                        {
                            remoteId = 2;
                        }
                        else
                        {
                            remoteId = 1;
                        }
                        outPacket << static_cast<uint8_t>(Status::Connected) << m_playerNumber << remoteId;
                        m_connectedClients.emplace_back(tempSocket);
                        m_selector.add(*m_connectedClients.back().GetSocket());
                        if (m_connectedClients.back().GetSocket()->send(outPacket) != sf::Socket::Done) //Send client id
                        {
                            std::cout << "Error sending player index" << std::endl;
                        }
                        std::cout << "Client connected:" << std::endl;
                        std::cout << "-Assigned id: " << static_cast<int>(m_playerNumber) << std::endl;
                        std::cout << "-Assigned remoteId: " << static_cast<int>(remoteId) << std::endl;
                        std::cout << std::endl;
                    }
                    else //server is full
                    {
                        sf::Packet outPacket;
                        outPacket << static_cast<uint8_t>(Status::Full);

                        if (tempSocket->send(outPacket) != sf::Socket::Done)
                        {
                            std::cout << "Server is full" << std::endl;
                        }
                        std::cout << "User tried to connect but the server was full" << std::endl;
                    }
                }
            }
            else
            {
                //Receive data
                for (auto& connectedClient : m_connectedClients)
                {
                    if (m_selector.isReady(*connectedClient.GetSocket()))
                    {
                        sf::Packet received;

                        if (connectedClient.GetSocket()->receive(received) == sf::Socket::Done)
                        {
                            connectedClient.SetTimeout(m_clock.getElapsedTime());
                            int8_t option;
                            received >> option;
                            const auto status = static_cast<Status>(option);

                            switch (status)
                            {
                            case Status::Connected:
                                {
                                    std::cout << "Client connected" << std::endl;
                                }
                            case Status::Disconnected:
                                {
                                    int8_t disconnectedPlayerId;
                                    received >> disconnectedPlayerId;
                                    m_selector.remove(*m_connectedClients[connectedClient.GetId()].GetSocket());
                                    const auto clientToBeRemoved = std::find_if(
                                        m_connectedClients.begin(), m_connectedClients.end(),
                                        [&connectedClient](const ConnectedClient& client)
                                        {
                                            return client.GetId() == connectedClient.GetId();
                                        });
                                    m_selector.remove(*connectedClient.GetSocket());
                                    m_connectedClients.erase(clientToBeRemoved);
                                    --m_playerNumber;
                                    SendDisconnect(disconnectedPlayerId);
                                    std::cout << "Client disconnected" << std::endl;
                                    std::cout << "Number of remianing players: " << static_cast<int>(m_playerNumber) << std::endl;
                                    if (m_playerNumber == 0)
                                    {
                                        m_connectedClients.clear();
                                        m_selector.clear();
                                    }
                                    break;
                                }
                            case Status::Movement:
                                {
                                    std::cout << "Server received movement data\n";
                                    SendMove(received, connectedClient.GetId());
                                    break;
                                }
                            case Status::Boxes:
                                {
                                    std::cout << "Server received boxes data \n";
                                    SendBoxes(received, connectedClient.GetId());
                                    break;
                                }
                            }
                        }

                        const auto tempTime = m_clock.getElapsedTime().asSeconds() - connectedClient
                                                                                     .GetTimeout().asSeconds();
                        if (tempTime >= 5)
                        {
                            std::cout << "Client timeout" << std::endl;
                            sf::Packet timeOutPacket;
                            timeOutPacket << 2;
                            timeOutPacket << connectedClient.GetId();

                            m_selector.remove(*m_connectedClients[connectedClient.GetId()].GetSocket());
                            const auto clientToBeRemoved = std::find_if(
                                m_connectedClients.begin(), m_connectedClients.end(),
                                [&connectedClient](const ConnectedClient& client)
                                {
                                    return client.GetId() == connectedClient.GetId();
                                });
                            m_connectedClients.erase(clientToBeRemoved);
                            --m_playerNumber;
                            std::cout << "Client disconnected" << std::endl;
                            std::cout << "Number of remianing players: " << static_cast<int>(m_playerNumber) << std::endl;
                        }
                    }
                }
            }
        }
    }
}

void Server::SendMove(sf::Packet& packet, const uint8_t skip)
{
    std::cout << "Sending packet to clients" << std::endl;
    for (size_t index = 0; index < m_connectedClients.size(); ++index)
    {
        if (skip == index)
        {
            continue;
        }
        std::cout << "Trying to send packet to client with id: " << index << std::endl;
        if (m_connectedClients[index].GetSocket()->send(packet) != sf::Socket::Done)
        {
            std::cout << "Error sending packet to client with id = " << index << std::endl;
        }
    }
}

void Server::SendBoxes(sf::Packet& packet, const uint8_t skip)
{
    std::cout << "Sending boxes to clients" << std::endl;
    for (size_t index = 0; index < m_connectedClients.size(); ++index)
    {
        if (skip == index)
        {
            continue;
        }
        std::cout << "Trying to send boxes to client with id: " << index << std::endl;
        if (m_connectedClients[index].GetSocket()->send(packet) != sf::Socket::Done)
        {
            std::cout << "Error sending packet to client with id = " << index << std::endl;
        }
    }
}

void Server::SendDisconnect(const int8_t disconnectedPlayerId)
{
    sf::Packet sent;
    sent << static_cast<uint8_t>(Status::Disconnected);
    sent << disconnectedPlayerId;
    std::cout << "Sending disconnection packet to clients" << std::endl;
    std::cout << "Disconnected player id: " << disconnectedPlayerId;
    for (size_t index = 0; index < m_connectedClients.size(); ++index)
    {
        std::cout << "Trying to send packet to client with id: " << index << std::endl;
        if (m_connectedClients[index].GetSocket()->send(sent) != sf::Socket::Done)
        {
            std::cout << "Error sending packet to client with id = " << index << std::endl;
        }
    }
}
