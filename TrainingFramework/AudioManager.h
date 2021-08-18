#pragma once
#include <string>
#include <SFML/Audio.hpp>
#include "StateBase.h"


class AudioManager {
protected:
	static AudioManager* ms_Instance;
public:
	static void CreateInstance();
	static AudioManager* GetInstance();
	static void DestroyInstance();

	sf::Music music;
	std::string musicFile;
	float volume;
	float pitch;
	
	void PlayMusic();
	void StopMusic();
	void Update();
	void SetVolume(float);
	float GetVolume();
	void SetPitch(float);
	float GetPitch();
	std::string GetMusicStatus();
	std::string GetMusic(StateBase*);
	std::string GetMusic(std::string);
	void AdjustAudio();
};