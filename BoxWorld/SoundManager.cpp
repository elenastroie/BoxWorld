#include "stdafx.h"
#include "SoundManager.h"

void SoundManager::LoadSounds() {
    if (!m_walkSoundBuffer.loadFromFile("./Assets/Sounds/walkSound.wav"))
    {
        throw std::exception("walkSound couldn't be loaded from file!");
    }
    if(!m_backgroundMusic.openFromFile("./Assets/Sounds/backgroundMusic.ogg"))
    {
        throw std::exception("backgroundMusic couldn't be opened");
    }
    if(!m_winSoundBuffer.loadFromFile("./Assets/Sounds/winSound.wav"))
    {
        throw std::exception("winSound couldn't be loaded from file!");
    }
}

void SoundManager::InitializeSounds() {
    m_backgroundMusic.setVolume(5);
    m_backgroundMusic.setLoop(true);

    m_walkSound.setBuffer(m_walkSoundBuffer);
    m_walkSound.setVolume(65);

    m_winSound.setBuffer(m_winSoundBuffer);
    m_winSound.setVolume(25);
}

SoundManager::SoundManager()
{
    LoadSounds();
    InitializeSounds();
}

void SoundManager::PlayWalkSound()
{
    m_walkSound.stop();
    m_walkSound.play();
}

void SoundManager::PlayWinSound()
{
    m_winSound.play();
}

void SoundManager::PlayMusic()
{
    m_backgroundMusic.play();
}

void SoundManager::StopWinSound()
{
    m_winSound.stop();
}

void SoundManager::StopMusic()
{
    m_backgroundMusic.stop();
}
