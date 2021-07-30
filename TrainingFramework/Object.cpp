#include "stdafx.h"
#include "Object.h"

Matrix Object::GetWVP()
{
	Matrix scale, rotationX, rotationY, rotationZ, translation;

	scale.SetScale(m_Scale);

	rotationX.SetRotationX(m_Rotation.x);
	rotationY.SetRotationY(m_Rotation.y);
	rotationZ.SetRotationZ(m_Rotation.z);

	translation.SetTranslation(m_Translation);

	Matrix worldMatrix = scale * rotationZ * rotationX * rotationY * translation;

	Matrix WVP = worldMatrix * Camera::GetInstance()->GetViewMatrix() * Camera::GetInstance()->GetProjection();
	return WVP;
}

Matrix Object::GetWVP(Camera* camera)
{
	Matrix scale, rotationX, rotationY, rotationZ, translation;

	scale.SetScale(m_Scale);

	rotationX.SetRotationX(m_Rotation.x);
	rotationY.SetRotationY(m_Rotation.y);
	rotationZ.SetRotationZ(m_Rotation.z);

	translation.SetTranslation(m_Translation);

	Matrix worldMatrix = scale * rotationZ * rotationX * rotationY * translation;

	Matrix WVP = worldMatrix * camera->GetViewMatrix() * camera->GetProjection();
	return WVP;
}

Object::Object()
{
	m_modelId = -1;
	m_spriteId = -1;
	m_shadersId = -1;
}

void Object::Init(ResourceManager* resource)
{
	if (m_modelId != -1)
		m_Model = resource->GetModel(m_modelId);

	if (m_spriteId != -1)
		m_Sprite = resource->GetSprite(m_spriteId);

	for (int i = 0; i < m_TextureIds.size(); i++)
	{
		Texture* texture = resource->GetTexture(m_TextureIds.at(i));
		m_Textures.push_back(texture);
	}

	for (int i = 0; i < m_CubeTextureIds.size(); i++)
	{
		Texture* cubeTexture = resource->GetCubeTexture(m_CubeTextureIds.at(i));
		m_Textures.push_back(cubeTexture);
	}

	m_Shaders = resource->GetShaders(m_shadersId);
}

void Object::SetSpriteId(int id)
{
	m_spriteId = id;
}

void Object::SetModelId(int id)
{
	m_modelId = id;
}

void Object::SetTranslation(Vector3 translation)
{
	m_Translation = translation;
}

void Object::Draw(Camera* camera)
{
	if (m_modelId != -1)
		m_Model->Model::BindBuffer();

	if (m_spriteId != -1)
		m_Sprite->Sprite::BindBuffer();

	for (int i = 0; i < m_Textures.size(); i++)
	{
		m_Textures.at(i)->BindBuffer(i);
	}

	m_Shaders->Use(GetWVP(camera));

	if (m_modelId != -1)
		m_Model->Model::Draw();

	if (m_spriteId != -1)
		m_Sprite->Sprite::Draw();

	if (m_modelId != -1)
		m_Model->Model::BindBuffer(false);

	if (m_spriteId != -1)
		m_Sprite->Sprite::BindBuffer(false);

	for (int i = 0; i < m_Textures.size(); i++)
	{
		m_Textures.at(i)->BindBuffer(i, false);
	}
}

void Object::SetTextureId(int id)
{
	m_TextureIds.push_back(id);
}

void Object::SetTextureCubeId(int id)
{
	m_CubeTextureIds.push_back(id);
}

void Object::SetShadersId(int id)
{
	m_shadersId = id;
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

}

Object::~Object()
{
	m_Model = NULL;
	m_Texture = NULL;
	m_Shaders = NULL;
	m_Sprite = NULL;

	m_TextureIds.clear();
}
