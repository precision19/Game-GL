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
	char type[10];

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
		memset(type, 0, sizeof(type));
		fscanf(f, "TYPE %s\n", type);
		strcpy(object->type, type);
		fscanf(f, "POSITION %f %f %f\n", &x, &y, &z);
		object->SetPosition(Vector3(x, y, z));

		fscanf(f, "ROTATION %f %f %f\n", &x, &y, &z);
		object->SetRotation(Vector3(x, y, z));

		fscanf(f, "SCALE %f %f %f\n", &x, &y, &z);
		object->SetScale(Vector3(x, y, z));

		fscanf(f, "RENDERER %d\n", &id);
		object->SetRenderer(id);

		object->SetNativeSize();

		m_vObjects.push_back(object);
	}

	fclose(f);
}

void SceneManager::AddPhysicsToScene()
{
	//make the ground
	b2Vec2 gravity(0.0f, -10.0f);
	m_world = std::make_unique<b2World>(gravity);
	m_world.get()->SetGravity(b2Vec2(0.0f, -10.0f));
	for (int i = 0; i < m_vObjects.size(); i++) {
		if (strncmp(m_vObjects[i]->type, "GROUND", 6) == 0) {
			GroundBox* grBox = new GroundBox();
			grBox->Init(m_world.get(), Vector2(m_vObjects[i]->GetPosition().x, m_vObjects[i]->GetPosition().y), Vector2(m_vObjects[i]->GetDimension().x, m_vObjects[i]->GetDimension().y));
			m_boxes.push_back(grBox);
			m_boxes[i]->SetDynamic(false);
		}
		else {
			DynamicBox* dyBox = new DynamicBox();
			dyBox->Init(m_world.get(), Vector2(m_vObjects[i]->GetPosition().x, m_vObjects[i]->GetPosition().y), Vector2(m_vObjects[i]->GetDimension().x, m_vObjects[i]->GetDimension().y));
			dyBox->setObj(m_vObjects[i]);
			m_boxes.push_back(dyBox);
			m_boxes[i]->SetDynamic(true);
		}
	}
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
	//printf("%d\n", jumpPressed);
	for (auto it = m_vObjects.begin(); it != m_vObjects.end(); it++)
	{
		(*it)->Update(deltaTime);
	}
	m_world->Step(deltaTime, 6, 2);

	for (int i = 0; i < m_boxes.size(); i++) 
	{
		if (m_boxes[i]->GetDynmaic()) {
			DynamicBox* dyBox = (DynamicBox*)m_boxes[i];
			// add force to player
			if (jumpPressed && strncmp(m_vObjects[i]->type, "PLAYER", 6) == 0 ) {
				dyBox->UpdatePlayer(m_world.get());
			}
			dyBox->Update(m_world.get());
		}
	}
}

void SceneManager::DestroyAllObjects()
{
	for (auto it = m_vObjects.begin(); it != m_vObjects.end(); it++)
	{
		delete (*it);
	}
	for (int i = 0; i < m_boxes.size(); i++) {
		delete m_boxes[i];
	}
	m_vObjects.clear();
}

SceneManager::~SceneManager()
{
	DestroyAllObjects();
}
