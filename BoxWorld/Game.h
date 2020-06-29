#pragma once
#include "TextureManagerImpl.h"
#include "LevelLoaderImpl.h"
#include "MultiplayerLevelLoader.h"
#include "SoundManager.h"
#include "Screen.h"
#include "Network.h"
#include "SFML/Network/IpAddress.hpp"

class Game
{
public:
    Game();
    ~Game();
    void Start();
    void Update();
    static Game& GetInstance();
    void InitializeMultiplayer(const std::string&);
    void UpdateHighscoreBoard();
    void Disconnect() const;

private:
    std::shared_ptr<GameManager> m_gameManager;
    LevelLoaderImpl m_levelLoaderImpl;
    MultiplayerLevelLoader m_multiplayerLevelLoader;
    TextureManagerImpl m_textureManager;
    SoundManager m_soundManager;
    std::vector<std::shared_ptr<Screen>> m_screens;
    std::unique_ptr<Network> m_network;
    sf::TcpSocket m_socket;
    MatrixPosition m_lastPositionSent;
    sf::Clock m_clock;
    sf::Time m_positionTimer;
    static Game* s_instance;
};

