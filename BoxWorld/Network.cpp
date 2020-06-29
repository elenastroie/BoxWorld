#include "stdafx.h"
#include "Network.h"
#include "Status.h"
#include "State.h"
#include "MultiPlayerLevel.h"
#include <SFML/Network/Packet.hpp>

Network::Network(sf::IpAddress& ip, const uint16_t port): m_connected(false)
{
    if (m_socket.connect(ip, port, sf::seconds(5)) != sf::Socket::Done)
    {
        std::cout << "Error connecting to server" << std::endl;
    }
    else
    {
        m_socket.setBlocking(false);
        std::cout << "Connected to server." << std::endl;
    }
}

void Network::Diconnect(const std::shared_ptr<GameManager>& gameManager)
{
    sf::Packet packet;
    packet << static_cast<int8_t>(Status::Disconnected);
    packet << gameManager->GetCurrentLevel()->GetPlayer()->GetId();

    if (m_socket.send(packet) != sf::Socket::Done)
    {
        std::cout << "Error sending disconnect command to server" << std::endl;
    }
    else
    {
        std::cout << "Disconnected" << std::endl;
    }
}

void Network::SendMove(const std::shared_ptr<GameManager>& gameManager)
{
    std::cout << "Trying to send move to server" << std::endl;
    if (m_connected)
    {
        sf::Packet packet;
        packet << static_cast<int8_t>(Status::Movement);
        const auto player = gameManager->GetCurrentLevel()->GetPlayer();
        const auto row = player->GetMatrixPosition().GetRowIndex();
        const auto col = player->GetMatrixPosition().GetColumnIndex();
        packet << player->GetId();
        packet << row;
        packet << col;

        if (m_socket.send(packet) != sf::Socket::Done)
        {
            std::cout << "Error sending move to server" << std::endl;
        }
        else
        {
            std::cout << "Move sent: MatrixPosition(" <<  row << ", " << col << ")"<< std::endl;
        }
    }
}

void Network::SendBoxes(const std::shared_ptr<GameManager>& gameManager)
{
    auto level = std::dynamic_pointer_cast<MultiPlayerLevel>(gameManager->GetCurrentLevel());
    const auto boxes = level->GetBoxes();
    const auto player = gameManager->GetCurrentLevel()->GetPlayer();
    sf::Packet packet;
    packet << static_cast<uint8_t>(Status::Boxes);
    packet << player->GetId();
    packet << boxes.size();
    for(auto& box : boxes)
    {
        packet << box->GetMatrixPosition().GetRowIndex();
        packet << box->GetMatrixPosition().GetColumnIndex();
    }
    if (m_socket.send(packet) != sf::Socket::Done)
    {
        std::cout << "Error sending boxes to server" << std::endl;
    }
    else
    {
        std::cout << "Number of boxes sent: " << boxes.size();
    }
}

void Network::Receive(const std::shared_ptr<GameManager>& gameManager)
{
    sf::Packet receivePacket;
    auto status = Status::Disconnected;
    auto level = std::dynamic_pointer_cast<MultiPlayerLevel>(gameManager->GetCurrentLevel());
    if (level == nullptr)
    {
        throw std::exception("SingePlayerLevel in multiplayer.");
    }
    auto player = level->GetPlayer();
    auto remotePlayer = level->GetRemotePlayer();
    if (m_socket.receive(receivePacket) == sf::Socket::Done)
    {
        uint8_t type;
        int8_t id;

        receivePacket >> type;
        receivePacket >> id;

        status = static_cast<Status>(type);

        if (status == Status::Connected) // you connected to server, get your ID
        {
            int8_t remoteId;

            receivePacket >> remoteId;
            if (player->GetId() == -1)
            {
                player->SetId(id);
                remotePlayer->SetId(remoteId);
                std::cout << "Connected to server:" << std::endl;
                std::cout << "-Id: " << static_cast<int>(player->GetId()) << std::endl;
                std::cout << "-Remote id: " << static_cast<int>(remotePlayer->GetId()) << std::endl;
            }
            m_connected = true;
        }
        else if (status == Status::Disconnected)
        {
            std::cout << "Remote player disconnected" << std::endl;
        }
        else if (status == Status::Full)
        {
            std::cout << "Server is full" << std::endl;
        }
        else if (status == Status::Movement)
        {
            size_t row;
            size_t col;
            receivePacket >> row;
            receivePacket >> col;
            std::cout << "Received MatrixPosition(" << row << ", " << col << ")" << std::endl;
            level->MoveRemotePlayer({row, col});
        }
        else if(status == Status::Boxes)
        {
            size_t size;
            receivePacket >> size;
            if(size!=level->GetBoxes().size())
            {
                throw std::exception("Different number of boxes");
            }
            std::cout << "-----BOXES-----" << std::endl;
            for(auto& box : level->GetBoxes())
            {
                size_t rowIndex;
                size_t colIndex;
                receivePacket >> rowIndex;
                receivePacket >> colIndex;
                std::cout<< "Received MatrixPosition(" << rowIndex << ", " << colIndex << ")" << std::endl;
                level->MoveRemoteBox(box, { rowIndex, colIndex });
            }
        }
    }
}
