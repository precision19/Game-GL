#pragma once
#include <string>
#include <SFML/Audio.hpp>
#include <vector>
#include <deque>

using namespace std;

class AudioManager {
protected:
	struct SoundData {
		sf::SoundBuffer soundBuffer;
		sf::Sound sound;
	};
	deque<SoundData> soundList;
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
	string GetMusicStatus();
	void PlayBackgroundMusic(string);
	void SetMusicFile(string);
	
	//Sound effect
	sf::Sound sound;
	//vector<sf::Sound> soundList;
	sf::SoundBuffer soundBuffer ;
	string soundFile;

	void PlaySoundEffect(string name, bool loop, float volume);
	void CheckPlay();
};