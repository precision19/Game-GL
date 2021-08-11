#include "stdafx.h"
#include "SceneManager.h"

SceneManager* SceneManager::ms_Instance = NULL;

void SceneManager::CreateInstance()
{
	if (ms_Instance == NULL)
		ms_Instance = new SceneManager();
}

SceneManager* SceneManager::GetInstance()
{
	return ms_Instance;
}

void SceneManager::DestroyInstance()
{
	if (ms_Instance)
	{
		delete ms_Instance;
		ms_Instance = NULL;
	}
}

SceneManager::SceneManager() { }


void SceneManager::LoadScene(string sceneName)
{
	DestroyAllObjects();

	string path = "Managers/" + sceneName + "SM.txt";

	FILE* f = fopen(path.c_str(), "r+");

	if (f == NULL)
	{
		printf("Invalid file %s\n", path.c_str());
		exit(1);
	}

	int amount, id;
	float x, y, z;
	char keyword[30];

	fscanf(f, "#Camera %d\n", &id);
	Camera::GetInstance()->SetPerspective(id);
	fscanf(f, "POSITION %f %f %f\n", &x, &y, &z);
	Camera::GetInstance()->SetPosition(Vector3(x, y, z));
	fscanf(f, "TARGET %f %f %f\n", &x, &y, &z);
	Camera::GetInstance()->SetTarget(Vector3(x, y, z));
	if (id)
	{
		fscanf(f, "FOVY %f\n", &x);
		Camera::GetInstance()->SetFOVY(x);
	}
	fscanf(f, "MOVE_SPEED %f\n", &x);
	Camera::GetInstance()->SetMoveSpeed(x);

	Camera::GetInstance()->Init();

	fscanf(f, "#Objects: %d\n", &amount);
	for (int i = 0; i < amount; i++)
	{
		fscanf(f, "ID %d\n", &id);
		if (id != i)
			printf("WARNING: Object's ID is not correct");
		Object* object = new Object();
		object->SetID(id);

		char type[10];
		fscanf(f, "TYPE %s\n", type);
		if (strncmp(type, "GROUND", 6) == 0) {
			object->type = GROUND;
		}
		if (strncmp(type, "PLAYER", 6) == 0) {
			object->type = PLAYER;
		}
		fscanf(f, "POSITION %f %f %f\n", &x, &y, &z);
		object->SetPosition(Vector3(x, y, z));

		fscanf(f, "ROTATION %f %f %f\n", &x, &y, &z);
		object->SetRotation(Vector3(x, y, z));

		fscanf(f, "SCALE %f %f %f\n", &x, &y, &z);
		object->SetScale(Vector3(x, y, z));

		fscanf(f, "DIMENSION %f %f\n", &x, &y);
		object->SetDimension(Vector2(x, y));

		fscanf(f, "RENDERER %d\n", &id);
		object->SetRenderer(id);

		object->SetNativeSize(0);

		m_vObjects.push_back(object);
	}


	/*Object* player = new Player(100, 3);
	strcpy(player->type,"PLAYER");
	player->SetPosition(Vector3(50, 300, 1));
	player->SetRotation(Vector3(0, 0, 0));
	player->SetScale(Vector3(1, 1, 1));
	player->SetRenderer(2);
	player->SetNativeSize(0);
	player->SetRenderer(3);
	player->SetNativeSize(1);
	m_vObjects.push_back(player);*/

	fclose(f);
}

void SceneManager::AddPhysicsToScene()
{
	Physic::GetInstance()->InitBox(m_vObjects);
}

void SceneManager::Draw()
{
	for (auto it = m_vObjects.begin(); it != m_vObjects.end(); it++)
	{
		(*it)->Draw();
	}
}

void SceneManager::Update(float deltaTime)
{
	for (auto it = m_vObjects.begin(); it != m_vObjects.end(); it++)
	{
		(*it)->Update(deltaTime);
	}
	Physic::GetInstance()->Update(deltaTime, m_vObjects);
}

void SceneManager::DestroyAllObjects()
{
	for (auto it = m_vObjects.begin(); it != m_vObjects.end(); it++)
	{
		delete (*it);
	}
	m_vObjects.clear();
}

SceneManager::~SceneManager()
{
	DestroyAllObjects();
}
