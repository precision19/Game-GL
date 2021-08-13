#include "stdafx.h"
#include "MenuState.h"

MenuState::MenuState()
{
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

		fscanf(f, "RENDERER %d\n", &id);
		object->SetRenderer(id);
		fscanf(f, "POSITION %f %f %f\n", &x, &y, &z);
		object->SetPosition(Vector3(x, y, z));
		fscanf(f, "ROTATION %f %f %f\n", &x, &y, &z);
		object->SetRotation(Vector3(x, y, z));
		fscanf(f, "SCALE %f %f %f\n", &x, &y, &z);
		object->SetScale(Vector3(x, y, z));

		m_Objects.push_back(object);
	}

	fscanf(f, "#PlayButton\n");
	m_PlayButton = new Button();
	fscanf(f, "RENDERER %d\n", &id);
	m_PlayButton->SetRenderer(id);
	fscanf(f, "RENDERER %d\n", &id);
	m_PlayButton->SetRenderer(id);
	fscanf(f, "POSITION %f %f %f\n", &x, &y, &z);
	m_PlayButton->SetPosition(Vector3(x, y, z));
	fscanf(f, "ROTATION %f %f %f\n", &x, &y, &z);
	m_PlayButton->SetRotation(Vector3(x, y, z));
	fscanf(f, "SCALE %f %f %f\n", &x, &y, &z);
	m_PlayButton->SetScale(Vector3(x, y, z));

	fscanf(f, "#SoundButton\n");
	m_SoundButton = new Button();
	fscanf(f, "RENDERER %d\n", &id);
	m_SoundButton->SetRenderer(id);
	fscanf(f, "RENDERER %d\n", &id);
	m_SoundButton->SetRenderer(id);
	fscanf(f, "POSITION %f %f %f\n", &x, &y, &z);
	m_SoundButton->SetPosition(Vector3(x, y, z));
	fscanf(f, "ROTATION %f %f %f\n", &x, &y, &z);
	m_SoundButton->SetRotation(Vector3(x, y, z));
	fscanf(f, "SCALE %f %f %f\n", &x, &y, &z);
	m_SoundButton->SetScale(Vector3(x, y, z));

	fclose(f);
}

void MenuState::SetStateManager(StateManager* stateManager)
{
	m_StateManager = stateManager;
}

void MenuState::OnStart()
{
	Camera::GetInstance()->SetDefault();
}


void MenuState::Update(float deltaTime)
{
	for (int i = 0; i < m_Objects.size(); i++)
	{
		m_Objects.at(i)->Update(deltaTime);
	}

	m_PlayButton->Update(deltaTime);
	m_SoundButton->Update(deltaTime);

	if (m_SoundButton->JustPressed())
	{
		// TODO: turn on/off sound
		printf("Sound button is clicked");
	}

	if (m_PlayButton->JustPressed())
	{
		// TODO: switch state
		m_StateManager->SwitchState("Level");	// TEMP
	}
}

void MenuState::Draw() 
{
	for (int i = 0; i < m_Objects.size(); i++)
	{
		m_Objects.at(i)->Draw();
	}

	m_PlayButton->Draw();
	m_SoundButton->Draw();
}

MenuState::~MenuState()
{

	for (int i = 0; i < m_Objects.size(); i++)
	{
		delete m_Objects.at(i);
	}

	delete m_PlayButton;
	delete m_SoundButton;
}
