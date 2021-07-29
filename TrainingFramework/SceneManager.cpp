#include "stdafx.h"
#include "SceneManager.h"

SceneManager* SceneManager::ms_Instance = NULL;

SceneManager::SceneManager()
{
	ResourceManager::CreateInstance();
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

		object->Init();
		m_vObjects.push_back(object);
	}
	
	return 0;
}

void SceneManager::KeyEventHandle(unsigned char key, bool isPressed)
{
	switch (key)
	{
	case 'W':
	case 'w':
		keyPressed = isPressed ? (keyPressed | MOVE_FORWARD) : (keyPressed ^ MOVE_FORWARD);
		break;
	case 'A':
	case 'a':
		keyPressed = isPressed ? (keyPressed | MOVE_LEFT) : (keyPressed ^ MOVE_LEFT);
		break;
	case 'S':
	case 's':
		keyPressed = isPressed ? (keyPressed | MOVE_BACKWARD) : (keyPressed ^ MOVE_BACKWARD);
		break;
	case 'D':
	case 'd':
		keyPressed = isPressed ? (keyPressed | MOVE_RIGHT) : (keyPressed ^ MOVE_RIGHT);
		break;
	case 'J':
	case 'j':
	case VK_SPACE:
		keyPressed = isPressed ? (keyPressed | MOVE_UP) : (keyPressed ^ MOVE_UP);
		break;
	case 'K':
	case 'k':
	case VK_CONTROL:
		keyPressed = isPressed ? (keyPressed | MOVE_DOWN) : (keyPressed ^ MOVE_DOWN);
		break;
	case 'Q':
	case 'q':
	case VK_LEFT:
		keyPressed = isPressed ? (keyPressed | ROTATE_LEFT) : (keyPressed ^ ROTATE_LEFT);
		break;
	case 'E':
	case 'e':
	case VK_RIGHT:
		keyPressed = isPressed ? (keyPressed | ROTATE_RIGHT) : (keyPressed ^ ROTATE_RIGHT);
		break;
	case 'U':
	case 'u':
	case VK_UP:
		keyPressed = isPressed ? (keyPressed | LOOK_UP) : (keyPressed ^ LOOK_UP);
		break;
	case 'I':
	case 'i':
	case VK_DOWN:
		keyPressed = isPressed ? (keyPressed | LOOK_DOWN) : (keyPressed ^ LOOK_DOWN);
		break;
	default:
		break;
	}
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
		(*it)->Draw();
	}
}

void SceneManager::Update(float deltaTime)
{
	Camera::GetInstance()->Update(keyPressed, deltaTime);

	for (auto it = m_vObjects.begin(); it != m_vObjects.end(); it++)
	{
		(*it)->Update(deltaTime);
	}
}

SceneManager::~SceneManager()
{
	Camera::DestroyInstance();
	ResourceManager::DestroyInstance();

	for (auto it = m_vObjects.begin(); it != m_vObjects.end(); it++)
	{
		delete (*it);
	}

	m_vObjects.clear();
}
