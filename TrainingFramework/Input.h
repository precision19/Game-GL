#pragma once
#include "Vertex.h"
#include <map>
#include "Globals.h"

using namespace std;

enum KeyCode
{
	Space,
	Ctrl,
	W,
	A,
	S,
	D,
	Up,
	Left,
	Down,
	Right
};

class Input
{
protected:
	static Input* ms_Instance;

	bool m_isTouching;
	Vector2 m_PreviousTouchPosition;
	Vector2 m_TouchPosition;
	int m_KeyPressed;
	map<unsigned, int> m_KeyMap;
public:
	static void CreateInstance();
	static Input* GetInstance();
	static void DestroyInstance();

	Input();
	~Input();
	static void SetKeyPressed(unsigned char, bool);
	static bool GetKeyDown(KeyCode);
	static bool GetKeyUp(KeyCode);
	static void SetTouchStatus(bool);
	static void SetTouchPosition(Vector2);
	static bool GetTouch();
	static Vector2 GetDeltaTouch();
	static Vector2 GetTouchPosition();
};

