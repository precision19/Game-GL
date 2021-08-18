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

void AudioManager::SetVolume(float volume) {
	this->volume = volume;
	this->music.setVolume(this->volume);
}


void AudioManager::SetPitch(float pitch) {
	this->pitch = pitch;
	this->music.setVolume(this->pitch);
}



float AudioManager::GetVolume() {
	return this->volume;
}

float AudioManager::GetPitch() {
	return this->pitch;
}

std::string AudioManager::GetMusic(StateBase* currentState) {
	if (currentState->GetName() == "Menu") this->musicFile = "Sounds/Menu.ogg";
	if (currentState->GetName() == "Map") this->musicFile = "Sounds/Map.ogg";
	if (currentState->GetName() == "Level") this->musicFile = "Sounds/Level1.ogg";
	std::cout << this->musicFile << std::endl;
	return this->musicFile;
}

std::string AudioManager::GetMusic(std::string musicFile) {
	return this->musicFile = musicFile;
}

std::string AudioManager::GetMusicStatus() {
	if (this->music.getStatus() == 0) return "Stopped";
	if (this->music.getStatus() == 1) return "Paused";
	if (this->music.getStatus() == 2) return "Playing";
}


void AudioManager::PlayMusic() {
	if (!music.openFromFile(this->musicFile)) {
		std::cout << "Error" << std::endl;
	}
	this->music.play();
	this->music.setLoop(true);
	std::cout << this->musicFile << std::endl;
}

void AudioManager::StopMusic() {
	this->music.stop();
}


void AudioManager::AdjustAudio() {

}

