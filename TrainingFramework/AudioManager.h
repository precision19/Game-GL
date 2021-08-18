#pragma once
#include <string>
#include <SFML/Audio.hpp>
#include <vector>

using namespace std;

class AudioManager {
protected:
	static AudioManager* ms_Instance;
public:
	static void CreateInstance();
	static AudioManager* GetInstance();
	static void DestroyInstance();

	AudioManager();
	void SetVolume(float);
	float GetVolume();
	void SetPitch(float);
	float GetPitch();

	//Music 
	sf::Music music;
	string musicFile;
	float volume;
	float pitch;
	
	void PlayMusic();
	void StopMusic();
	string GetMusicStatus();
	void PlayBackgroundMusic(string);
	void SetMusicFile(string);
	
	//Sound effect
	sf::Sound sound;
	//vector<sf::Sound> soundList;
	sf::SoundBuffer soundBuffer ;
	string soundFile;

	void AddSound(string);
	void PlaySound(bool);
	void StopSound();
	string GetSoundStatus();
	void PlaySoundEffect(string, bool);
	void SetSoundFile(string);
};