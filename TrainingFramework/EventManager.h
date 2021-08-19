#pragma once
#include <vector>

using namespace std;

#define EVENT_GROUP_GAMEPLAY 0
#define EVENT_PLAYER_DIE 0
#define EVENT_PLAYER_WIN 1
#define EVENT_PLAYER_SCORE 2

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

