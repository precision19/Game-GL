#include "stdafx.h"
#include "Button.h"

Button::Button(Vector2 position, Vector2 size)
{
	m_Target = NULL;

	m_Position = position;
	m_Size = size;

	m_IsSkipped = false;
	m_IsPressing = false;
}

void Button::SetSize(Vector2 size)
{
	m_Size = size;
}

void Button::AddListener(Component* component, int functionID)
{
	m_Components.push_back(component);
	m_CallBackFunctionIDs.push_back(functionID);
}

void Button::Update(float deltaTime)
{
	if (!Input::GetTouch())
	{
		m_IsSkipped = false;
		return;
	}

	if (m_IsSkipped) return;

	if (Input::GetTouch()) 
	{
		if (!m_IsPressing)
		{
			if (CheckClick())
				m_IsPressing = true;
			else
				m_IsSkipped = true;
		}
		else
		{
			if (Input::GetDeltaTouch().Length() > 1.0)
			{
				m_IsPressing = false;
				m_IsSkipped = true;
			}
		}
	}
	else 
	{
		if (m_IsPressing)
		{
			m_IsPressing = false;
			OnClick();
		}
		m_IsSkipped = false;
	}
}

bool Button::CheckClick()
{
	Vector2 distance = Input::GetTouchPosition() - m_Position;
	if ((distance.x <= m_Size.x / 2) && (distance.x >= -m_Size.x / 2)
		&& (distance.y <= m_Size.y / 2) && (distance.y >= -m_Size.y / 2))
		return true;
	return false;
}

void Button::OnClick()
{
	for (int i = 0; i < m_Components.size(); i++)
		m_Components.at(i)->CallBack(m_CallBackFunctionIDs.at(i));
}
