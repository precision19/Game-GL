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
	m_ButtonClicked = 0;
}

Input::~Input()
{

}

void Input::SetButtonBuffer(int buttonID)
{
	ms_Instance->m_ButtonClicked = ms_Instance->m_ButtonClicked | (1 << buttonID);
}

bool Input::CheckButtonBuffer(int buttonID)
{
	if (ms_Instance->m_ButtonClicked & (1 << buttonID))
	{
		ms_Instance->m_ButtonClicked = ms_Instance->m_ButtonClicked ^ (1 << buttonID);
		return true;
	}
	return false;
}

bool Input::GetKeyDown(KeyCode key) {
	return (ms_Instance->m_KeyPressed & (1 << key));
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