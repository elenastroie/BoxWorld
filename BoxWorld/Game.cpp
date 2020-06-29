#include "stdafx.h"
#include "Game.h"
#include "../Logging/Log.h"
#include "TextureManagerImpl.h"
#include "ScreenStatus.h"
#include "MultiplayerGameManager.h"
#include "SinglePlayerGameManager.h"
#include "GameScreen.h"
#include "MenuScreen.h"
#include "../Logging/TimeLogger.h"
#include "InstructionsScreen.h"
#include "PlayerInfoScreen.h"
#include "HighscoreScreen.h"
#include "ConnectionScreen.h"
Game* Game::s_instance = nullptr;

Game::Game()
{
    m_textureManager.LoadAllTextures({
        "red_box.png", "yellow_box.png",
        "simple_tile.png",
        "target.png",
        "wall.png", "wall_bg.png", "score_bg.png",
        "best_solution.png", "not_best_solution.png",
        "player_00.png", "player_10.png",
        "player_20.png", "player_30.png",
        "player_01.png", "player_11.png",
        "player_21.png", "player_31.png",
        "path_indicator.png"
        });

    m_soundManager.PlayMusic();
    s_instance = this;
    m_gameManager = std::make_shared<SinglePlayerGameManager>(m_levelLoaderImpl, m_soundManager);
}

Game::~Game()
{
    if (std::dynamic_pointer_cast<MultiplayerGameManager>(m_gameManager))
    {
        m_network->Diconnect(m_gameManager);
    }
}

void Game::InitializeMultiplayer(const std::string& ip)
{
    m_gameManager = std::make_shared<MultiplayerGameManager>(m_multiplayerLevelLoader, m_soundManager);
    sf::IpAddress ipAddress(ip);
    m_network = std::make_unique<Network>(ipAddress, 51850);
    m_socket.setBlocking(false);
    m_lastPositionSent = m_gameManager->GetCurrentLevel()->GetPlayer()->GetMatrixPosition();
}

void Game::UpdateHighscoreBoard()
{
    auto ofstream = std::ofstream("Assets/Player/highscore.txt", std::ios::app);
    if (!ofstream.is_open())
    {
        ofstream.open("Assets/Player/highscore.txt", std::ios::app);
    }
    auto ifstream = std::ifstream("Assets/Player/player_info.txt");
    int numberOfPlayers;
    std::string nameOfPlayer;
    int highscorePlayer;
    if (ifstream.peek() != std::ifstream::traits_type::eof())
    {
        ifstream >> numberOfPlayers;
        ifstream >> nameOfPlayer;
        ifstream >> highscorePlayer;
        ifstream.close();
        auto currentPlayer = std::to_string(numberOfPlayers) + " " + nameOfPlayer + " >" + std::to_string(highscorePlayer);
        std::string line;
        bool samePlayer = 0;
        ifstream.open("Assets/Player/highscore.txt");
        if (ifstream.is_open()) {
            while (std::getline(ifstream, line))
            {
                if (line.find(currentPlayer, 0) != std::string::npos)
                {
                    samePlayer = 1;
                    break;
                }
            }
        }
        ifstream.close();
        if (samePlayer == 0)
        {
            ifstream.close();
            ofstream << numberOfPlayers << " " << nameOfPlayer << " >" << highscorePlayer << '\n';
            ofstream.close();
        }
    }
}
void Game::Disconnect() const
{
    m_network->Diconnect(m_gameManager);
}

void Game::Start()
{
    auto ostream = std::ofstream();
    ostream.open("BoxWorld.log", std::ofstream::out | std::ofstream::app);
    static auto fileLogger = TimeLogger(ostream, Logger::Level::Info);
    Log::RegisterLogger(fileLogger);

    static auto consoleLogger = TimeLogger(std::cerr, Logger::Level::Info);
    Log::RegisterLogger(consoleLogger);
    Log::Info("BoxWorld started");

    sf::RenderWindow window(sf::VideoMode(896, 896, 32), "BoxWorld");
    window.setMouseCursorVisible(true);

    auto currentScreen = ScreenStatus::MENU;
    m_screens.push_back(std::make_shared<MenuScreen>());
    m_screens.push_back(std::make_shared<GameScreen>()); //singlePlayer
    m_screens.push_back(std::make_shared<GameScreen>()); //multiPlayer
    m_screens.push_back(std::make_shared<InstructionsScreen>());
    m_screens.push_back(std::make_shared<PlayerInfoScreen>());
    m_screens.push_back(std::make_shared<HighscoreScreen>());
    m_screens.push_back(std::make_shared<ConnectionScreen>());

    currentScreen = m_screens[0]->Run(window);

    if (currentScreen == ScreenStatus::PLAY || currentScreen == ScreenStatus::INSTRUCTIONS || currentScreen ==
        ScreenStatus::HIGHSCORE)
    {
        m_gameManager = std::make_shared<SinglePlayerGameManager>(m_levelLoaderImpl, m_soundManager);
    }
    else if (currentScreen == ScreenStatus::CONNECTION_SCREEN)
    {
    }
    else if (currentScreen == ScreenStatus::RESTART)
    {
        currentScreen = ScreenStatus::PLAY;
    }
    auto ifstream = std::ifstream("Assets/Player/player_info.txt");
    std::ofstream ofstream;
    if (!ifstream.is_open())
    {
        ofstream.open("Assets/Player/player_info.txt");
        ofstream.close();
    }
    if (currentScreen == ScreenStatus::PLAY)
    {
        ofstream.open("Assets/Player/player_info.txt");
        ofstream << "1";
        ofstream.close();
        currentScreen = ScreenStatus::INFO_PLAYER;
    }
    while (currentScreen != ScreenStatus::EXIT)
    {
        currentScreen = m_screens[static_cast<int8_t>(currentScreen)]->Run(window);
        if (currentScreen == ScreenStatus::MENU)
        {
            UpdateHighscoreBoard();
        }
        if (currentScreen == ScreenStatus::INFO_PLAYER && std::dynamic_pointer_cast<SinglePlayerGameManager>(
            m_gameManager))
        {
            currentScreen = ScreenStatus::PLAY;
        }
        if (currentScreen == ScreenStatus::PLAY && std::dynamic_pointer_cast<MultiplayerGameManager>(m_gameManager))
        {
            ofstream = std::ofstream("Assets/Player/player_info.txt");
            ofstream << "1";
            ofstream.close();
            currentScreen = ScreenStatus::INFO_PLAYER;
            m_network->Diconnect(m_gameManager);
            m_gameManager = std::make_shared<SinglePlayerGameManager>(m_levelLoaderImpl, m_soundManager);
        }
        if (currentScreen == ScreenStatus::RESTART && std::dynamic_pointer_cast<MultiplayerGameManager>(m_gameManager))
        {
            currentScreen = ScreenStatus::MULTIPLAYER;
            continue;
        }
        if (currentScreen == ScreenStatus::MULTIPLAYER && std::dynamic_pointer_cast<SinglePlayerGameManager>(
            m_gameManager))
        {
            m_gameManager = std::make_shared<MultiplayerGameManager>(m_multiplayerLevelLoader, m_soundManager);
            const auto connectionScreen = std::dynamic_pointer_cast<ConnectionScreen>(
                m_screens[static_cast<int8_t>(ScreenStatus::CONNECTION_SCREEN)]);
            const auto ip = connectionScreen->GetValidIp();
            InitializeMultiplayer(ip);
        }
        if (currentScreen == ScreenStatus::RESTART && std::dynamic_pointer_cast<SinglePlayerGameManager>(m_gameManager))
        {
            const auto playScreen = std::dynamic_pointer_cast<GameScreen>(
                m_screens[static_cast<int8_t>(ScreenStatus::PLAY)]);
            playScreen->ResetElapesLevelTime();
            currentScreen = ScreenStatus::PLAY;
        }
        if (std::dynamic_pointer_cast<MultiplayerGameManager>(m_gameManager))
        {
            Update();
        }
        if (currentScreen == ScreenStatus::PLAY)
        {
            if (!ifstream.is_open())
            {
                std::string line;
                ifstream.open("Assets/Player/player_info.txt");
                if (!std::getline(ifstream,line))
                {
                    ofstream.open("Assets/Player/player_info.txt");
                    ofstream << "1";
                    ofstream.close();
                    currentScreen = ScreenStatus::INFO_PLAYER;
                }
                ifstream.close();
            }
        }
    }
    if (std::dynamic_pointer_cast<MultiplayerGameManager>(m_gameManager))
    {
        m_network->Diconnect(m_gameManager);
    }
    UpdateHighscoreBoard();
    Log::Info("Exit");
    Log::UnregisterAllLoggers();
}

void Game::Update()
{
    auto& manager = GameManager::GetInstance();
    const auto multiplayerGameManager = dynamic_cast<MultiplayerGameManager*>(&manager);
    if (multiplayerGameManager == nullptr)
    {
        return;
    }
    const auto player = m_gameManager->GetCurrentLevel()->GetPlayer();
    //Send direction
    if (m_lastPositionSent != player->GetMatrixPosition())
    {
        m_network->SendMove(m_gameManager); // send move data
        m_network->SendBoxes(m_gameManager);
        m_lastPositionSent = player->GetMatrixPosition();
    }

    //Send position 1 time every 1 second
    m_positionTimer += m_clock.restart();
    if (m_positionTimer >= sf::seconds(1))
    {
        m_network->SendMove(m_gameManager);
        m_network->SendBoxes(m_gameManager);
        m_positionTimer = sf::Time::Zero;
    }

    //Recive data from network
    m_network->Receive(m_gameManager);
}

Game& Game::GetInstance()
{
    return *s_instance;
}
