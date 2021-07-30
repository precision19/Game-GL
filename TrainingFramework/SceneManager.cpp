#include "stdafx.h"
#include "SceneManager.h"

SceneManager* SceneManager::ms_Instance = NULL;

SceneManager::SceneManager()
{
	//ResourceManager::CreateInstance();

	string path = "Managers/LevelsMap";
	path += "RM.txt";

	m_Resource = new ResourceManager(path.c_str());
}

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
		object->SetTranslation(Vector3(x, y, z));

		fscanf(f, "ROTATION %f %f %f\n", &x, &y, &z);
		object->SetRotation(Vector3(x, y, z));

		fscanf(f, "SCALE %f %f %f\n", &x, &y, &z);
		object->SetScale(Vector3(x, y, z));

		object->Init(m_Resource);
		m_vObjects.push_back(object);
	}
}

int SceneManager::Init()
{
	ifstream ifile;
	ifile.open("Managers/SM.txt");

	if (ifile.fail())
	{
		printf("Invalid File Name!");
		exit(1);
	}

	string str = "";
	char keyword[20];
	int count, id;

	getline(ifile, str);
	sscanf(str.c_str(), "%s %d", keyword, &count);
	if (strcmp(keyword, "#Cameras:"))
	{
		printf("ERROR: Invalid File Format - Expected #Cameras:");
		return -1;
	}
	for (int i = 0; i < count; i++)
	{
		getline(ifile, str);

		sscanf(str.c_str(), "%s %d", keyword, &id);
		if (id != i)
		{
			printf("WARNING: cameraId is incorrect");
		}
		Camera::CreateInstance();

		int x, y, z;
		float f;

		getline(ifile, str);
		sscanf(str.c_str(), "%s %d %d %d", keyword, &x, &y, &z);
		Camera::GetInstance()->SetPosition(Vector3(x, y, z));

		getline(ifile, str);
		sscanf(str.c_str(), "%s %d %d %d", keyword, &x, &y, &z);
		Camera::GetInstance()->SetTarget(Vector3(x, y, z));

		getline(ifile, str);
		sscanf(str.c_str(), "%s %d %d %d", keyword, &x, &y, &z);
		Camera::GetInstance()->SetUpVector(Vector3(x, y, z));

		getline(ifile, str);
		sscanf(str.c_str(), "%s %f", keyword, &f);
		Camera::GetInstance()->SetFOVY(f);

		getline(ifile, str);
		sscanf(str.c_str(), "%s %f", keyword, &f);
		Camera::GetInstance()->SetNear(f);

		getline(ifile, str);
		sscanf(str.c_str(), "%s %f", keyword, &f);
		Camera::GetInstance()->SetFar(f);

		getline(ifile, str);
		sscanf(str.c_str(), "%s %f", keyword, &f);
		Camera::GetInstance()->SetMoveSpeed(f);

		getline(ifile, str);
		sscanf(str.c_str(), "%s %f", keyword, &f);
		Camera::GetInstance()->SetRotateSpeed(f);

		Camera::GetInstance()->Init();
	}
	getline(ifile, str);
	// Load light
	getline(ifile, str);
	sscanf(str.c_str(), "%s %d", keyword, &count);
	if (strcmp(keyword, "#Lights:"))
	{
		printf("ERROR: Invalid File Format - Expected #Lights:");
		return -1;
	}
	for (int i = 0; i < count; i++)
	{
		getline(ifile, str);
		getline(ifile, str);
		getline(ifile, str);
		getline(ifile, str);

	}
	getline(ifile, str);
	// Load Object
	getline(ifile, str);
	sscanf(str.c_str(), "%s %d", keyword, &count);
	if (strcmp(keyword, "#Objects:"))
	{
		printf("ERROR: Invalid File Format - Expected #Objects:");
		return -1;
	}
	for (int i = 0; i < count; i++)
	{
		getline(ifile, str);
		sscanf(str.c_str(), "%s %d ", keyword, &id);
		if (id != i)
		{
			printf("WARNING: objectId is incorrect");
		}
		Object* object = new Object();
		// MODEL
		getline(ifile, str);
		sscanf(str.c_str(), "%s %d", keyword, &id);
		object->SetModelId(id);
		// TEXTURES
		int count2;
		getline(ifile, str);
		sscanf(str.c_str(), "%s %d", keyword, &count2);
		for (int i = 0; i < count2; i++)
		{
			getline(ifile, str);
			sscanf(str.c_str(), "%s %d", keyword, &id);
			object->SetTextureId(id);
		}
		// CUBETEXTURE
		getline(ifile, str);
		sscanf(str.c_str(), "%s %d", keyword, &count2);
		for (int i = 0; i < count2; i++)
		{
			getline(ifile, str);
			sscanf(str.c_str(), "%s %d", keyword, &id);
			object->SetTextureCubeId(id);
		}
		// SHADERS
		getline(ifile, str);
		sscanf(str.c_str(), "%s %d", keyword, &id);
		object->SetShadersId(id);
		// LIGHTS
		getline(ifile, str);
		sscanf(str.c_str(), "%s %d", keyword, &count2);
		for (int i = 0; i < count2; i++)
		{
			getline(ifile, str);
		}
		float x, y, z;
		// POSITION
		getline(ifile, str);
		sscanf(str.c_str(), "%s %f %f %f", keyword, &x, &y, &z);
		object->SetTranslation(Vector3(x, y, z));
		// ROTATION
		getline(ifile, str);
		sscanf(str.c_str(), "%s %f %f %f", keyword, &x, &y, &z);
		object->SetRotation(Vector3(x, y, z));
		// SCALE
		getline(ifile, str);
		sscanf(str.c_str(), "%s %f %f %f", keyword, &x, &y, &z);
		object->SetScale(Vector3(x, y, z));

		object->Init(m_Resource);
		m_vObjects.push_back(object);
	}

	Object* sprite = new Object();
	sprite->SetSpriteId(0);
	sprite->SetShadersId(0);
	sprite->SetTextureId(0);
//	sprite->SetSizeBoard(Vector2(0.0, 0.0), Vector2(480, 854), Vector2(480, 854));
	sprite->SetTranslation(Vector3(0.0, 1.0, 0.0));
	sprite->SetRotation(Vector3(0.0, 0.0, 0.0));
	sprite->SetScale(Vector3(1.0, 1.0, 1.0));
	sprite->Init();
	m_spObjects.push_back(sprite);
	
	return 0;
}

void SceneManager::CreateInstance()
{
	if (ms_Instance == NULL)
		ms_Instance = new SceneManager();
}

SceneManager* SceneManager::GetInstance()
{
	if (ms_Instance == NULL)
		ms_Instance = new SceneManager();
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

void SceneManager::Draw()
{
	for (auto it = m_vObjects.begin(); it != m_vObjects.end(); it++)
	{
		(*it)->Draw(m_Camera);
	}

	for (auto it2 = m_spObjects.begin(); it2 != m_spObjects.end(); it2++)
	{
		(*it2)->Draw();
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
	Camera::DestroyInstance();
	//ResourceManager::DestroyInstance();
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
