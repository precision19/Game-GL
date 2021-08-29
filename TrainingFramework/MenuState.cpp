#include "stdafx.h"
#include "MenuState.h"

MenuState::MenuState()
{
	m_Name = "Menu";
	m_IsFirst = true;
	string path = "Managers/MenuSM.txt";
	FILE* f = fopen(path.c_str(), "r+");
	if (f == NULL)
	{
		printf("Invalid file %s\n", path.c_str());
		exit(1);
	}
		int amount, id;
	float x, y, z;
	char keyword[20], name[20];

	fscanf(f, "#Objects: %d\n", &amount);
	for (int i = 0; i < amount; i++)
	{
		fscanf(f, "%s %s\n", keyword, name);

		Object* object = new Object(name);

		fscanf(f, "RENDERER %s\n", name);
		object->SetRenderer(name);
		fscanf(f, "POSITION %f %f %f\n", &x, &y, &z);
		object->SetPosition(Vector3(x, y, z));
		fscanf(f, "ROTATION %f %f %f\n", &x, &y, &z);
		object->SetRotation(Vector3(x, y, z));
		fscanf(f, "SCALE %f %f %f\n", &x, &y, &z);
		object->SetScale(Vector3(x, y, z));

		if (object->GetName() == "Logo")
		{
			m_Logo = object;
		}
		else
		{
			m_Objects.push_back(object);
		}
	}

	fscanf(f, "#PlayButton\n");
	Button* PlayButton = new Button();
	fscanf(f, "RENDERER %s\n", name);
	PlayButton->SetRenderer(name);
	fscanf(f, "RENDERER %s\n", name);
	PlayButton->SetRenderer(name);
	fscanf(f, "POSITION %f %f %f\n", &x, &y, &z);
	PlayButton->SetPosition(Vector3(x, y, z));
	fscanf(f, "ROTATION %f %f %f\n", &x, &y, &z);
	PlayButton->SetRotation(Vector3(x, y, z));
	fscanf(f, "SCALE %f %f %f\n", &x, &y, &z);
	PlayButton->SetScale(Vector3(x, y, z));
	PlayButton->SetButtonID(BUTTON_PLAY);

	fscanf(f, "#SoundButton\n");
	Button* SoundButton = new Button();
	fscanf(f, "RENDERER %s\n", name);
	SoundButton->SetRenderer(name);
	fscanf(f, "RENDERER %s\n", name);
	SoundButton->SetRenderer(name);
	fscanf(f, "POSITION %f %f %f\n", &x, &y, &z);
	SoundButton->SetPosition(Vector3(x, y, z));
	fscanf(f, "ROTATION %f %f %f\n", &x, &y, &z);
	SoundButton->SetRotation(Vector3(x, y, z));
	fscanf(f, "SCALE %f %f %f\n", &x, &y, &z);
	SoundButton->SetScale(Vector3(x, y, z));
	SoundButton->SetButtonID(BUTTON_SOUND);

	m_Objects.push_back(PlayButton);
	m_Objects.push_back(SoundButton);

	fclose(f);

}

void MenuState::SetStateManager(StateManager* stateManager)
{
	m_StateManager = stateManager;
}

void MenuState::OnStart()
{
	Camera::GetInstance()->SetDefault();
	AudioManager::GetInstance()->PlayBackgroundMusic(m_Name);

	if (m_IsFirst)
	{
		m_Logo->GetRenderer()->SetOpacity(0.0);
		EffectManager::GetInstance()->AddFadedEffect(m_Logo, 1.0, 3.0, EVENT_LOGO_SHOWNED);
		FlagManager::GetInstance()->Set(FLAG_MENU_STATUS, MENU_ON_WELCOME);
	}
	else
	{
		FlagManager::GetInstance()->Set(FLAG_MENU_STATUS, MENU_ON_DEFAULT);
	}
}


void MenuState::Update(float deltaTime)
{
	if (FlagManager::GetInstance()->Check(FLAG_MENU_STATUS, MENU_ON_WELCOME))
	{
		if (EventManager::GetInstance()->CheckEvent(EVENT_GROUP_EFFECT, EVENT_LOGO_SHOWNED))
		{
			EffectManager::GetInstance()->AddFadedEffect(m_Logo, 0.0, 2.0, EVENT_LOGO_HIDED);
			//EffectManager::GetInstance()->AddMoveEffect(m_Logo, Vector3(1024, 0, -1), 2.0, EVENT_LOGO_HIDED);
			FlagManager::GetInstance()->Set(FLAG_MENU_STATUS, MENU_ON_HIDING_WELCOME);
		}
	}
	else if (FlagManager::GetInstance()->Check(FLAG_MENU_STATUS, MENU_ON_HIDING_WELCOME))
	{
		if (EventManager::GetInstance()->CheckEvent(EVENT_GROUP_EFFECT, EVENT_LOGO_HIDED))
		{
			FlagManager::GetInstance()->Set(FLAG_MENU_STATUS, MENU_ON_DEFAULT);
		}
	}
	else if (FlagManager::GetInstance()->Check(FLAG_MENU_STATUS, MENU_ON_DEFAULT))
	{
		for each (Object * object in m_Objects)
				object->Update(deltaTime);

		if (Input::CheckButtonBuffer(BUTTON_SOUND))
		{
			// TODO: turn on/off sound
			printf("Sound button is clicked");
		}
		if (Input::CheckButtonBuffer(BUTTON_PLAY))
		{
			// TODO: switch state
			m_StateManager->SwitchState("Map");	// TEMP
		}
	}
}

void MenuState::Draw() 
{
	if (FlagManager::GetInstance()->Check(FLAG_MENU_STATUS, MENU_ON_DEFAULT, MENU_ON_HIDING_WELCOME))
	{
		for each (Object * object in m_Objects)
			object->Draw();
	}

	if (FlagManager::GetInstance()->Check(FLAG_MENU_STATUS, MENU_ON_WELCOME, MENU_ON_HIDING_WELCOME))
		m_Logo->Draw();
}

MenuState::~MenuState()
{
	for each (Object * object in m_Objects)
		delete object;

	delete m_Logo;
}
