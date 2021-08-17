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


void AudioManager::PlayMusic(std::string musicFile) {
	this->musicFile = musicFile;
	if (!this->music.openFromFile(this->musicFile)) {
		std::cout << "ERROR" << std::endl;
	}
	this->music.play();
	this->music.setLoop(true);
}

void AudioManager::StopMusic() {
	this->music.stop();
}

void AudioManager::Update() {
}

void AudioManager::AdjustAudio() {

}

