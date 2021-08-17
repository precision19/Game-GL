#pragma once
#include <string>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class AudioManager {
protected:
	static AudioManager* ms_Instance;
public:
	static void CreateInstance();
	static AudioManager* GetInstance();
	static void DestroyInstance();

	Music music;
	string musicFile;
	float volume;
	float pitch;
	
	void Init(float, float);
	void PlayMusic(string);
	void StopMusic();
	void Update();
	void SetVolume(float);
	float GetVolume();
	void SetPitch(float);
	float GetPitch();
	void AdjustAudio();
};