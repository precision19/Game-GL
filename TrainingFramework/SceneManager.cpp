#include "stdafx.h"
#include "SceneManager.h"

SceneManager::SceneManager(const char* sceneName)
{
	string pathRM = string(sceneName) + "RM.txt";
	m_Resource = new ResourceManager(pathRM.c_str());

	string pathSM = string(sceneName) + "SM.txt";
	Init(pathSM.c_str());
	//make the ground
	b2Vec2 gravity(0.0f, -9.81f);
	m_world = std::make_unique<b2World>(gravity);
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(500.0f, -1000.0f);
	b2Body* groundBody = m_world->CreateBody(&groundBodyDef);
	//make the ground fixture
	b2PolygonShape groundBox;
	groundBox.SetAsBox(1000.0f, 1000.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	for (int i = 0; i < m_vObjects.size(); i++) {
		Box newBox;
		newBox.Init(m_world.get(), Vector2(m_vObjects[i]->GetPosition().x, m_vObjects[i]->GetPosition().y), Vector2(m_vObjects[i]->GetDimension().x, m_vObjects[i]->GetDimension().y));
		m_boxes.push_back(newBox);
		printf("%f %f\n", m_vObjects[i]->GetDimension().x, m_vObjects[i]->GetDimension().y);
	}
}

SceneManager::SceneManager(string name)
{

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
		(*it)->Draw();
	}
}

void SceneManager::Update(float deltaTime)
{
	for (auto it = m_vObjects.begin(); it != m_vObjects.end(); it++)
	{
		(*it)->Update(deltaTime);
	}
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	m_world->Step(deltaTime, velocityIterations, positionIterations);
	for (int i = 0; i < m_boxes.size(); i++) {
		m_vObjects[i]->SetPosition(Vector3(m_boxes[i].getBody()->GetPosition().x, m_boxes[i].getBody()->GetPosition().y, m_vObjects[i]->GetPosition().z));
	}
}

SceneManager::~SceneManager()
{
	delete m_Resource;

	for (auto it = m_vObjects.begin(); it != m_vObjects.end(); it++)
	{
		delete (*it);
	}

	m_vObjects.clear();
}
