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
	if (!music.openFromFile(musicFile))
	{
		std::cout << "Error: Can not play music in file " << musicFile << std::endl;
	}
	music.play();
	music.setLoop(true);
	std::cout << "Playing music in file: " << musicFile << std::endl;
}


//Sound effect
void AudioManager::PlaySoundEffect(string name, bool isLoop, float volume) {
	soundFile = "Sounds/" + name + ".wav";
	SoundData tmpData;
	soundList.push_back(tmpData);
	soundList.back().soundBuffer.loadFromFile(soundFile);
	soundList.back().sound.setBuffer(soundList.back().soundBuffer);
	soundList.back().sound.setLoop(isLoop);
	soundList.back().sound.setVolume(volume);
	soundList.back().sound.play();
}

void AudioManager::CheckPlay() {
	for (int i = 0; i < soundList.size(); i++) {
		if (soundList[i].sound.getStatus() != 2) soundList.erase(soundList.begin() + i);
	}
}
