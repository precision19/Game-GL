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

float AudioManager::GetVolume() {
	return volume;
}

float AudioManager::GetPitch() {
	return pitch;
}

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


AudioManager::AudioManager()
{
	musicFile = "";
	volume = 1;
	pitch = 1;
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


void AudioManager::AdjustAudio() 
{

}

