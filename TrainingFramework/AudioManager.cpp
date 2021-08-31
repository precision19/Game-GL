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

AudioManager::AudioManager()
{
	musicFile = "";
	soundFile = "";
	musicVolume = 100.0f;
	soundVolume = 100.0f;
	isMusicMute = false;
	isSoundMute = false;
	isMuteAll = false;
}

//Music
void AudioManager::SetMusicVolume(float volume) 
{
	//if (volume == 0.0f) isMusicMute = true;
	//else isMusicMute = false;
	musicVolume = volume;
	music.setVolume(volume);
}


float AudioManager::GetMusicVolume() {
	return musicVolume;
}

bool AudioManager::IsMusicMute() {
	return isMusicMute;
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

void AudioManager::MuteMusic() {
	isMusicMute = true;
	SetMusicVolume(0.0f);
}

void AudioManager::UnmuteMusic() {
	isMusicMute = false;
	SetMusicVolume(100.0f);
}

//Sound effect
bool AudioManager::IsSoundMute() {
	return isSoundMute;
}

void AudioManager::MuteSound() {
	isSoundMute = true;
}

void AudioManager::UnmuteSound() {
	isSoundMute = false;
}

void AudioManager::PlaySoundEffect(string name, bool isLoop, float volume) {
	soundFile = "Sounds/" + name + ".wav";
	SoundData tmpData;
	soundList.push_back(tmpData);
	soundList.back().soundBuffer.loadFromFile(soundFile);
	soundList.back().sound.setBuffer(soundList.back().soundBuffer);
	soundList.back().sound.setLoop(isLoop);
	if(isSoundMute == false) soundList.back().sound.setVolume(volume);
	else soundList.back().sound.setVolume(0.0f);
	soundList.back().sound.play();
}

void AudioManager::CheckPlay() {
	for (int i = 0; i < soundList.size(); i++) {
		if (soundList[i].sound.getStatus() != 2) soundList.erase(soundList.begin() + i);
	}
}

bool AudioManager::IsMuteAll() {
	if (isMusicMute == true && isSoundMute == true) return true;
	else return false;
}

void AudioManager::MuteAll() {
	MuteMusic();
	MuteSound();
}

void AudioManager::UnmuteAll() {
	UnmuteMusic();
	UnmuteSound();
}