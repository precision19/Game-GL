#pragma once
#include "Vertex.h"
#include <map>
#include "Globals.h"

using namespace std;

#define BUTTON_PLAY -1
#define BUTTON_SOUND -2
#define BUTTON_MENU -3
#define BUTTON_START -4
#define BUTTON_PAUSE -5

class Input
{
protected:
	static Input* ms_Instance;

	bool m_isTouching;
	Vector2 m_PreviousTouchPosition;
	Vector2 m_TouchPosition;
	int m_ButtonClicked;
public:
	static void CreateInstance();
	static Input* GetInstance();
	static void DestroyInstance();

	Input();
	~Input();
	static void SetButtonBuffer(int);
	static bool CheckButtonBuffer(int);

	static void SetTouchStatus(bool);
	static void SetTouchPosition(Vector2);
	static bool GetTouch();
	static Vector2 GetDeltaTouch();
	static Vector2 GetTouchPosition();
};

