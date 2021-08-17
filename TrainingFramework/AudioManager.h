#pragma once
#include <string>
#include <SFML/Audio.hpp>


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
	
	void Init(float, float);
	void PlayMusic(std::string);
	void StopMusic();
	void Update();
	void SetVolume(float);
	float GetVolume();
	void SetPitch(float);
	float GetPitch();
	void AdjustAudio();
};