#include "stdafx.h"
#include "AudioManager.h"
#include <iostream>

AudioManager* AudioManager::ms_Instance = NULL;

void AudioManager::CreateInstance()
{
	if (ms_Instance == NULL)
		ms_Instance = new AudioManager();
}

AudioManager* AudioManager::GetInstance()
{
	return ms_Instance;
}

void AudioManager::DestroyInstance()
{
	if (ms_Instance)
	{
		delete ms_Instance;
		ms_Instance = NULL;
	}
}

void AudioManager::SetVolume(float volume) 
{
	volume = volume;
	music.setVolume(volume);
}

void AudioManager::SetPitch(float pitch) 
{
	pitch = pitch;
	music.setVolume(pitch);
}

AudioManager::AudioManager()
{
	musicFile = "";
	soundFile = "";
	volume = 1;
	pitch = 1;
}

float AudioManager::GetVolume() {
	return volume;
}

float AudioManager::GetPitch() {
	return pitch;
}

//Music
void AudioManager::SetMusicFile(string name) 
{
	if (name == "Menu") 
		musicFile = "Sounds/Menu.ogg";
	else if (name == "Map") 
		musicFile = "Sounds/Map.ogg";
	else if (name == "Level") 
		musicFile = "Sounds/Level1.ogg";

	std::cout << this->musicFile << std::endl;
}

std::string AudioManager::GetMusicStatus() 
{
	if (music.getStatus() == 0) return "Stopped";
	if (music.getStatus() == 1) return "Paused";
	if (music.getStatus() == 2) return "Playing";
}

void AudioManager::PlayBackgroundMusic(string name)
{
	musicFile = "Sounds/" + name + ".ogg";
	PlayMusic();
}


void AudioManager::PlayMusic()
{
	if (!music.openFromFile(musicFile)) 
	{
		std::cout << "Error: Can not play music in file " << musicFile << std::endl;
	}
	music.play();
	music.setLoop(true);
	std::cout << "Playing music in file: " << musicFile << std::endl;
}

void AudioManager::StopMusic() 
{
	this->music.stop();
}
//Sound effect
void AudioManager::SetSoundFile(string name)
{
	soundFile = "Sounds/" + name + ".wav";
	std::cout << this->soundFile << std::endl;
}

void AudioManager::PlaySound(bool isLoop) {
	if (!soundBuffer.loadFromFile(soundFile)) {
		std::cout << "Error: Can not play sound in file " << soundFile << std::endl;
	}
	sound.setBuffer(soundBuffer);
	if (isLoop) sound.setLoop(true);
	sound.play();
	std::cout << "Playing sound in file: " << soundFile << std::endl;
}

void AudioManager::PlaySoundEffect(string name, bool isLoop)
{
	soundFile = "Sounds/" + name + ".wav";
	PlaySound(isLoop);
}

