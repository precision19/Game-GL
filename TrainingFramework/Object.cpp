#include "stdafx.h"
#include "Object.h"

Matrix Object::GetWVP()
{
	Matrix scale, rotationX, rotationY, rotationZ, translation;

	scale.SetScale(m_Scale);

	rotationX.SetRotationX(m_Rotation.x);
	rotationY.SetRotationY(m_Rotation.y);
	rotationZ.SetRotationZ(m_Rotation.z);

	translation.SetTranslation(m_Position);

	Matrix worldMatrix = scale * rotationZ * rotationX * rotationY * translation;

	//Matrix WVP = worldMatrix * camera->GetViewMatrix() * camera->GetProjection();
	Matrix WVP = worldMatrix * Camera::GetInstance()->GetViewMatrix() * Camera::GetInstance()->GetProjection();
	return WVP;
}

Object::Object()
{
	m_Model = NULL;
	m_Shaders = NULL;
}

void Object::SetNativeSize()
{
	Vector2 size = m_Textures[0]->GetSize();
	m_Scale = Vector3(size.x, size.y, 1);
}

void Object::SetModel(int modelID)
{
	m_Model = ResourceManager::GetInstance()->GetModel(modelID);
}

void Object::SetModel(string modelName)
{
	m_Model = ResourceManager::GetInstance()->GetModel(modelName);
}

void Object::AddTexture(int textureID)
{
	m_Textures.push_back(ResourceManager::GetInstance()->GetTexture(textureID));
}

void Object::AddTexture(string textureName)
{
	m_Textures.push_back(ResourceManager::GetInstance()->GetTexture(textureName));
}

void Object::AddCubeTexture(int cubeTextureID)
{
	m_Textures.push_back(ResourceManager::GetInstance()->GetCubeTexture(cubeTextureID));
}

void Object::SetShaders(int shadersID)
{
	m_Shaders = ResourceManager::GetInstance()->GetShaders(shadersID);
}

void Object::SetSahders(string shadersName)
{
	m_Shaders = ResourceManager::GetInstance()->GetShaders(shadersName);
}

void Object::SetPosition(Vector3 position)
{
	m_Position = position;
}

void Object::Draw()
{
	if (m_Model == NULL || m_Shaders == NULL)
		return;

	m_Model->Model::BindBuffer();

	for (int i = 0; i < m_Textures.size(); i++)
	{
		m_Textures.at(i)->BindBuffer(i);
	}

	m_Shaders->Use(GetWVP());

	m_Model->Model::Draw();

	m_Model->Model::BindBuffer(false);

	for (int i = 0; i < m_Textures.size(); i++)
	{
		m_Textures.at(i)->BindBuffer(i, false);
	}
}

Vector3 Object::GetPosition() {
	return m_Position;
}

void Object::SetScale(Vector3 scale)
{
	m_Scale = scale;
}

void Object::SetRotation(Vector3 rotation)
{
	m_Rotation = rotation * PI / 180;
}

void Object::Update(float deltaTime)
{
	for (int i = 0; i < m_Components.size(); i++)
	{
		m_Components.at(i)->Update(deltaTime);
	}
}

Object::~Object()
{
	m_Model = NULL;
	m_Textures.clear();
	m_Shaders = NULL;
}
