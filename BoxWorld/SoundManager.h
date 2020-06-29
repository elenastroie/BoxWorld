#pragma once
#include <SFML/Audio.hpp>

class SoundManager
{
public:
    void LoadSounds();
    void InitializeSounds();
    SoundManager();
    ~SoundManager() = default;

    void PlayWalkSound();
    void PlayWinSound();
    void PlayMusic();
    void StopWinSound();
    void StopMusic();

private:
    sf::SoundBuffer m_walkSoundBuffer;
    sf::SoundBuffer m_winSoundBuffer;
    sf::Sound m_walkSound;
    sf::Sound m_winSound;
    sf::Music m_backgroundMusic;
};
