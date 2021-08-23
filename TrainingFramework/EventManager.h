#pragma once
#include <vector>

using namespace std;

#define EVENT_GROUP_GAMEPLAY 0
#define EVENT_PLAYER_DIE 0
#define EVENT_PLAYER_WIN 1
#define EVENT_PLAYER_SCORE 2
#define EVENT_GAME_STOP 3
#define EVENT_GAME_RESTART 4
#define EVENT_EFFECT_START 5
#define EVENT_EFFECT_DONE 6

#define ON_ d

class EventManager
{
protected:
	static EventManager* ms_Instance;
	vector<int> m_Events;
public:
	static void CreateInstance();
	static EventManager* GetInstance();
	static void DestroyInstance();
	EventManager();
	void InvokeEvent(int, int);
	bool CheckEvent(int, int, bool = true);
};
