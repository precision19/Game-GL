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
	Button* PlayButton = new Button();
	fscanf(f, "RENDERER %d\n", &id);
	PlayButton->SetRenderer(id);
	fscanf(f, "RENDERER %d\n", &id);
	PlayButton->SetRenderer(id);
	fscanf(f, "POSITION %f %f %f\n", &x, &y, &z);
	PlayButton->SetPosition(Vector3(x, y, z));
	fscanf(f, "ROTATION %f %f %f\n", &x, &y, &z);
	PlayButton->SetRotation(Vector3(x, y, z));
	fscanf(f, "SCALE %f %f %f\n", &x, &y, &z);
	PlayButton->SetScale(Vector3(x, y, z));
	PlayButton->SetButtonID(BUTTON_PLAY);

	fscanf(f, "#SoundButton\n");
	Button* SoundButton = new Button();
	fscanf(f, "RENDERER %d\n", &id);
	SoundButton->SetRenderer(id);
	fscanf(f, "RENDERER %d\n", &id);
	SoundButton->SetRenderer(id);
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
}


void MenuState::Update(float deltaTime)
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
		m_StateManager->SwitchState("Level");	// TEMP
	}
}

void MenuState::Draw() 
{
	for each (Object * object in m_Objects)
		object->Draw();
}

MenuState::~MenuState()
{
	for each (Object * object in m_Objects)
		delete object;
}
