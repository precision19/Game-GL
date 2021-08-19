#include "stdafx.h"
#include "MapState.h"

MapState::MapState() 
{
	m_Name = "Map";

	string path = "Managers/LevelsMapSM.txt";

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
		Object* object = NULL;
		fscanf(f, "TYPE %s\n", name);
		if (strcmp(name, "LEVEL_BUTTON") == 0)
		{
			object = new Button(name);
			fscanf(f, "BUTTON_ID %d\n", &id);
			((Button*)object)->SetButtonID(id);
			fscanf(f, "RENDERER %s\n", name);
			object->SetRenderer(name);
		}
		else
		{
			object = new Object(name);
		}

		fscanf(f, "RENDERER %s\n", name);
		object->SetRenderer(name);
		fscanf(f, "POSITION %f %f %f\n", &x, &y, &z);
		object->SetPosition(Vector3(x, y, z));
		fscanf(f, "ROTATION %f %f %f\n", &x, &y, &z);
		object->SetRotation(Vector3(x, y, z));
		fscanf(f, "SCALE %f %f %f\n", &x, &y, &z);
		object->SetScale(Vector3(x, y, z));

		m_Objects.push_back(object);
	}

	fclose(f);
}

void MapState::SetStateManager(StateManager* stateManager)
{
	m_StateManager = stateManager;
}

void MapState::OnStart()
{
	// Refresh level button
	Camera::GetInstance()->SetDefault();
	AudioManager::GetInstance()->PlayBackgroundMusic(m_Name);
}

void MapState::Update(float deltaTime) 
{
	for each (Object * object in m_Objects)
		object->Update(deltaTime);

	for (int i = 1; i <= 21; i++)
	{
		if (Input::CheckButtonBuffer(i))
		{
			printf("open level %d\n", i);
			m_StateManager->SwitchState("Level");
		}
	}
}

void MapState::Draw() 
{
	for each (Object * object in m_Objects)
		object->Draw();
}

MapState::~MapState()
{
	for each (Object * object in m_Objects)
		delete object;
}
