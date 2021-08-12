#include "stdafx.h"
#include "Button.h"

Button::Button()
{
	m_IdleRenderer = NULL;
	m_OnPressRenerer = NULL;
	m_IsSkipped = false;
	m_IsPressing = false;
	m_WasJustPressed = false;
}

void Button::SetRenderer(int id)
{
	if (m_IdleRenderer == NULL)
	{
		m_IdleRenderer = PrefabManager::GetInstance()->GetRenderer(id)->Clone();
		m_Renderer = m_IdleRenderer;
	}
	else
	{
		m_OnPressRenerer = PrefabManager::GetInstance()->GetRenderer(id)->Clone();
	}
}

void Button::Update(float deltaTime)
{
	if (!Input::GetTouch())
	{
		if (m_IsPressing)
		{
			m_IsPressing = false;
			OnClicked();
			Idle();
		}
		m_IsSkipped = false;
		return;
	}

	if (m_IsSkipped) return;

	if (Input::GetTouch()) 
	{
		if (!m_IsPressing)
		{
			if (CheckClick())
			{
				m_IsPressing = true;
				OnPressing();
			}
			else
				m_IsSkipped = true;
		}
		else
		{
			if (Input::GetDeltaTouch().Length() > 10.0)
			{
				m_IsPressing = false;
				m_IsSkipped = true;
				//m_Renderer = m_IdleRenderer;
				Idle();
			}
		}
	}
}

bool Button::JustPressed()
{
	if (m_WasJustPressed)
	{
		Idle();
		m_WasJustPressed = false;
		return true;
	}
	return false;
}

Button::~Button()
{
	delete m_OnPressRenerer;
}

bool Button::CheckClick()
{
	Vector2 position = Vector2(m_Transform.position.x, m_Transform.position.y);
	Vector2 distance = Input::GetTouchPosition() - position;

	Vector2 size = Vector2(m_Renderer->GetTextureSize().x * m_Transform.scale.x, m_Renderer->GetTextureSize().y * m_Transform.scale.y);

	if ((distance.x <= size.x / 2) && (distance.x >= -size.x / 2)
		&& (distance.y <= size.y / 2) && (distance.y >= -size.y / 2))
		return true;

	return false;
}

void Button::Idle()
{
	m_Renderer = m_IdleRenderer;
}

void Button::OnPressing()
{
	m_Renderer = m_OnPressRenerer;
}

void Button::OnClicked()
{
	m_WasJustPressed = true;
}
