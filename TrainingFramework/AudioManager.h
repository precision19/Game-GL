#pragma once
#include <string>
#include <SFML/Audio.hpp>
#include <string>

using namespace std;

class AudioManager {
protected:
	static AudioManager* ms_Instance;
public:
	static void CreateInstance();
	static AudioManager* GetInstance();
	static void DestroyInstance();

	sf::Music music;
	string musicFile;
	float volume;
	float pitch;

	AudioManager();
	
	void PlayMusic();
	void StopMusic();
	void SetVolume(float);
	float GetVolume();
	void SetPitch(float);
	float GetPitch();
	string GetMusicStatus();
	void PlayBackgroundMusic(string);
	void SetMusicFile(string);
	void AdjustAudio();
};