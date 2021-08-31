#include "stdafx.h"
#include "LevelButton.h"

Vector3 LevelButton::m_StarPosition[3] = {Vector3(-22, -26, 0), Vector3(2, -26, 0), Vector3(26, -26,0)};

void LevelButton::Idle()
{
	if (m_Star >= 0)
		m_Renderer = m_IdleRenderer;
}

void LevelButton::OnPressing()
{
	if (m_Star >= 0)
	{
		if (m_OnPressRenerer != NULL)
			m_Renderer = m_OnPressRenerer;
	}
}

void LevelButton::OnClicked()
{
	if (m_Star >= 0)
		Input::SetButtonBuffer(m_ButtonID);
}

LevelButton::LevelButton()
{
	m_Star = -1;
	m_OnLockRenderer = NULL;
	m_StarRenderer = NULL;
}

LevelButton::LevelButton(string name) : Button(name)
{
	m_Star = -1;
	m_OnLockRenderer = NULL;
	m_StarRenderer = NULL;
}

void LevelButton::SetRenderer(int id)
{
	if (m_IdleRenderer == NULL)
		m_IdleRenderer = PrefabManager::GetInstance()->GetRenderer(id)->Clone();
	else if (m_OnPressRenerer == NULL)
		m_OnPressRenerer = PrefabManager::GetInstance()->GetRenderer(id)->Clone();
	else if (m_OnLockRenderer == NULL)
		m_OnLockRenderer = PrefabManager::GetInstance()->GetRenderer(id)->Clone();
	else if (m_StarRenderer == NULL)
		m_StarRenderer = PrefabManager::GetInstance()->GetRenderer(id)->Clone();
}

void LevelButton::SetRenderer(string name)
{
	if (m_IdleRenderer == NULL)
		m_IdleRenderer = PrefabManager::GetInstance()->GetRenderer(name)->Clone();
	else if (m_OnPressRenerer == NULL)
		m_OnPressRenerer = PrefabManager::GetInstance()->GetRenderer(name)->Clone();
	else if (m_OnLockRenderer == NULL)
		m_OnLockRenderer = PrefabManager::GetInstance()->GetRenderer(name)->Clone();
	else if (m_StarRenderer == NULL)
		m_StarRenderer = PrefabManager::GetInstance()->GetRenderer(name)->Clone();
}

void LevelButton::SetStar()
{
	m_Star = PlayerPrefs::GetInstance()->GetData(m_ButtonID);
	if (m_Star < 0)
	{
		m_Renderer = m_OnLockRenderer;
		if (m_OnLockRenderer == NULL)
			printf("WARNING: level button %d don't have on-lock-renderer", m_ButtonID);
	}
	else
		m_Renderer = m_IdleRenderer;
}

void LevelButton::Draw()
{
	if (m_Renderer == NULL)
		printf("WARNING: object %s have no renderer", m_Name.c_str());
	else
		m_Renderer->Draw(m_Transform);

	for (int i = 0; i < m_Star; i++)
	{
		Transform copy = m_Transform;
		copy.position = m_Transform.position + m_StarPosition[i];
		m_StarRenderer->Draw(copy);
	}
}

LevelButton::~LevelButton()
{
	delete m_OnLockRenderer;
	delete m_StarRenderer;
}
