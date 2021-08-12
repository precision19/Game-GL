#include "stdafx.h"
#include "Input.h"

Input* Input::ms_Instance = NULL;

void Input::CreateInstance()
{
	if (ms_Instance == NULL)
	{
		ms_Instance = new Input();
	}
}

void Input::DestroyInstance()
{
	if (ms_Instance)
	{
		delete ms_Instance;
		ms_Instance = NULL;
	}
}

Input* Input::GetInstance()
{
	return ms_Instance;
}

Input::Input()
{
	m_isTouching = false;
	m_TouchPosition = Vector2();
	m_PreviousTouchPosition = m_TouchPosition;

	m_KeyPressed = 0;

	m_KeyMap[VK_SPACE] = Space;
	m_KeyMap[VK_CONTROL] = Ctrl;
	m_KeyMap['W'] = W;
	m_KeyMap['w'] = W;
	m_KeyMap['A'] = A;
	m_KeyMap['a'] = A;
	m_KeyMap['S'] = S;
	m_KeyMap['s'] = S;
	m_KeyMap['D'] = D;
	m_KeyMap['d'] = D;
	m_KeyMap[VK_UP] = Up;
	m_KeyMap[VK_LEFT] = Left;
	m_KeyMap[VK_DOWN] = Down;
	m_KeyMap[VK_RIGHT] = Right;
}

Input::~Input()
{

}

void Input::SetKeyPressed(unsigned char key, bool isPressed)
{
	int keyId = ms_Instance->m_KeyMap[key];
	ms_Instance->m_KeyPressed = isPressed ? (ms_Instance->m_KeyPressed | (1 << keyId)) : (ms_Instance->m_KeyPressed ^ (1 << keyId));
}

bool Input::GetKeyDown(KeyCode key)
{
	return (ms_Instance->m_KeyPressed & (1 << key));
}

bool Input::GetKeyUp(KeyCode key)
{
	return !(ms_Instance->m_KeyPressed & (1 << key));
}

void Input::SetTouchStatus(bool status)
{
	ms_Instance->m_isTouching = status;
	ms_Instance->m_PreviousTouchPosition = ms_Instance->m_TouchPosition;
}

void Input::SetTouchPosition(Vector2 position)
{
	ms_Instance->m_PreviousTouchPosition = ms_Instance->m_TouchPosition;
	ms_Instance->m_TouchPosition = position;
}

bool Input::GetTouch()
{
	return ms_Instance->m_isTouching;
}

Vector2 Input::GetDeltaTouch()
{
	return ms_Instance->m_TouchPosition - ms_Instance->m_PreviousTouchPosition;
}

Vector2 Input::GetTouchPosition()
{
	Vector2 touchPosition = ms_Instance->m_TouchPosition;
	touchPosition.x -= Globals::screenWidth / 2;
	touchPosition.y -= Globals::screenHeight / 2;
	return touchPosition;
}