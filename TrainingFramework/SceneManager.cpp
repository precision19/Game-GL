#include "stdafx.h"
#include "SceneManager.h"

SceneManager::SceneManager(const char* sceneName)
{
	string pathRM = string(sceneName) + "RM.txt";
	m_Resource = new ResourceManager(pathRM.c_str());

	string pathSM = string(sceneName) + "SM.txt";
	Init(pathSM.c_str());
}

void SceneManager::Init(const char* filePath)
{
	FILE* f = fopen(filePath, "r+");

	if (f == NULL)
	{
		printf("Invalid file %s\n", filePath);
		exit(1);
	}

	int amount, id;
	float x, y, z;
	char keyword[30];

	fscanf(f, "#Camera %d\n", &id);
	m_Camera = new Camera(id);
	fscanf(f, "POSITION %f %f %f\n", &x, &y, &z);
	m_Camera->SetPosition(Vector3(x, y, z));
	fscanf(f, "TARGET %f %f %f\n", &x, &y, &z);
	m_Camera->SetTarget(Vector3(x, y, z));
	if (id)
	{
		fscanf(f, "FOVY %f\n", &x);
		m_Camera->SetFOVY(x);
	}
	fscanf(f, "MOVE_SPEED %f\n", &x);
	m_Camera->SetMoveSpeed(x);
	m_Camera->Init();
	
	fscanf(f, "#Objects: %d\n", &amount);
	for (int i = 0; i < amount; i++)
	{
		fscanf(f, "ID %d\n", &id);
		if (id != i)
			printf("WARNING: Object's ID is not correct");

		Object* object = new Object();
		fscanf(f, "MODEL_ID %d\n", &id);
		object->SetModelId(id);
		
		int amount2;
		fscanf(f, "AMOUNT_OF_TEXTURES %d\n", &amount2);
		for (int j = 0; j < amount2; j++)
		{
			fscanf(f, "TEXTURE_ID %d\n", &id);
			object->SetTextureId(id);
		}

		fscanf(f, "AMOUNT_OF_CUBETEXTURES %d\n", &amount2);
		for (int j = 0; j < amount2; j++)
		{
			fscanf(f, "TEXTURE_ID %d\n", &id);
			object->SetTextureCubeId(id);
		}

		fscanf(f, "SHADER_ID %d\n", &id);
		object->SetShadersId(id);

		fscanf(f, "POSITION %f %f %f\n", &x, &y, &z);
		object->SetPosition(Vector3(x, y, z));

		fscanf(f, "ROTATION %f %f %f\n", &x, &y, &z);
		object->SetRotation(Vector3(x, y, z));

		fscanf(f, "SCALE %f %f %f\n", &x, &y, &z);
		object->SetScale(Vector3(x, y, z));

		object->Init(m_Resource);

		fscanf(f, "SET_NATIVE_SIZE %d\n", &x);
		if (x) object->SetNativeSize();

		m_vObjects.push_back(object);
	}

	fclose(f);
}

void SceneManager::Draw()
{
	for (auto it = m_vObjects.begin(); it != m_vObjects.end(); it++)
	{
		(*it)->Draw(m_Camera);
	}

	for (auto it2 = m_spObjects.begin(); it2 != m_spObjects.end(); it2++)
	{
		(*it2)->Draw(m_Camera);
	} 
}

void SceneManager::Update(float deltaTime)
{
	//Camera::GetInstance()->Update(deltaTime);
	m_Camera->Update(deltaTime);

	for (auto it = m_vObjects.begin(); it != m_vObjects.end(); it++)
	{
		(*it)->Update(deltaTime);
	}

	for (auto it2 = m_spObjects.begin(); it2 != m_spObjects.end(); it2++)
	{
		(*it2)->Update(deltaTime);
	} 
}

SceneManager::~SceneManager()
{
	delete m_Resource;
	delete m_Camera;

	for (auto it = m_vObjects.begin(); it != m_vObjects.end(); it++)
	{
		delete (*it);
	}

	for (auto it2 = m_spObjects.begin(); it2 != m_spObjects.end(); it2++)
	{
		delete (*it2);
	} 

	m_vObjects.clear();
	m_spObjects.clear();
}
