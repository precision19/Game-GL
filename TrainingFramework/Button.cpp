#include "stdafx.h"
#include "Button.h"

Button::Button()
{
	m_Name = "Button";
	m_IdleRenderer = NULL;
	m_OnPressRenerer = NULL;
	m_IsSkipped = false;
	m_IsPressing = false;
}

Button::Button(string name)
{
	m_Name = name;
	m_IdleRenderer = NULL;
	m_OnPressRenerer = NULL;
	m_IsSkipped = false;
	m_IsPressing = false;
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

void Button::SetRenderer(string name)
{
	if (m_IdleRenderer == NULL)
	{
		m_IdleRenderer = PrefabManager::GetInstance()->GetRenderer(name)->Clone();
		m_Renderer = m_IdleRenderer;
	}
	else
	{
		m_OnPressRenerer = PrefabManager::GetInstance()->GetRenderer(name)->Clone();
	}
}

void Button::SetButtonID(int id)
{
	m_ButtonID = id;
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
				AudioManager::GetInstance()->PlaySoundEffect("Click", false);
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
				Idle();
			}
		}
	}
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
	if (m_OnPressRenerer != NULL)
		m_Renderer = m_OnPressRenerer;
}

void Button::OnClicked()
{
	Input::SetButtonBuffer(m_ButtonID);
}

Button::~Button()
{
	delete m_OnPressRenerer;
}
