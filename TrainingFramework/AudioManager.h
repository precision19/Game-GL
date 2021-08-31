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
	bool IsMuteAll();
	void MuteAll();
	void UnmuteAll();
	bool isMuteAll;
	//Music 
	sf::Music music;
	string musicFile;
	float musicVolume;
	bool isMusicMute;
	void PlayBackgroundMusic(string);
	void SetMusicFile(string);
	void SetMusicVolume(float);
	float GetMusicVolume();
	void MuteMusic();
	void UnmuteMusic();
	bool IsMusicMute();
	//Sound effect
	float soundVolume;
	sf::Sound sound;
	sf::SoundBuffer soundBuffer ;
	string soundFile;
	bool isSoundMute;
	void PlaySoundEffect(string name, bool loop, float volume);
	void CheckPlay();
	void MuteSound();
	void UnmuteSound();
	bool IsSoundMute();
};