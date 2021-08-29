#pragma once
#include <vector>

using namespace std;

#define FLAG_GAME_STATUS 0
#define GAME_ON_READY 1
#define GAME_ON_PLAYING 2
#define GAME_ON_PAUSE 3
#define GAME_ON_WIN 4
#define GAME_ON_RESTARTING 5

#define FLAG_MENU_STATUS 1
#define MENU_ON_WELCOME 1
#define MENU_ON_HIDING_WELCOME 2
#define MENU_ON_DEFAULT 3
#define MENU_ON_CREDIT 4

class FlagManager
{
protected:
	static FlagManager* ms_Instance;
	static const int m_FlagNumber = 5;
	vector<unsigned int> m_Flags;
public:
	static void CreateInstance();
	static FlagManager* GetInstance();
	static void DestroyInstance();

	FlagManager();
	void Set(int, int);
	bool Check(int, int);
	bool Check(int, int, int);
};

