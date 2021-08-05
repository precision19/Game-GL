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
	currentFrameTime = 0.3;
	anim_cursor = 0;
	currentFrameId = NULL;
}

void Object::SetNativeSize()
{
	Vector2 size = m_Textures[0]->GetSize();
	m_Scale = Vector3(size.x, size.y, 1);
	m_Dimension = size;
	printf("%f %f\n", size.x, size.y);
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

void Object::SetShaders(string shadersName)
{
	m_Shaders = ResourceManager::GetInstance()->GetShaders(shadersName);
}

void Object::SetCurrentFrame(int id)
{
	currentFrameId = id;
}

void Object::SetPosition(Vector3 position)
{
	m_Position = position;
}

void Object::Draw()
{
	anim_cursor += currentFrameTime;
	if (m_Model == NULL || m_Shaders == NULL)
		return;
//	printf("Texture %d\n", currentFrameId);
	m_Model->Model::BindBuffer();
	if (anim_cursor > 0.1)
	{
		currentFrameId = (currentFrameId + 1) % m_Textures.size();
		anim_cursor = 0;
	}
	m_Textures.at(currentFrameId)->BindBuffer(currentFrameId, TRUE);
	m_Shaders->Use(GetWVP());

	m_Model->Model::Draw();
	Sleep(100);

	m_Model->Model::BindBuffer(false);
	m_Textures.at(currentFrameId)->BindBuffer(currentFrameId, FALSE);

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
