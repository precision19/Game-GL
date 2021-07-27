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

	Matrix WVP = worldMatrix * Camera::GetInstance()->GetViewMatrix() * Camera::GetInstance()->GetPerspective();
	return WVP;
}

Object::Object()
{
	m_modelId = -1;
	m_textureCubeId = -1;
	m_textureId = -1;
	m_shadersId = -1;
}

void Object::Init()
{
	m_Model = ResourceManager::GetInstance()->GetModel(m_modelId);

	//if (m_textureCubeId != -1)
	//	m_Texture = ResourceManager::GetInstance()->GetCubeTexture(m_textureCubeId);
	//else 
	//	m_Texture = ResourceManager::GetInstance()->GetTexture(m_textureId);

	for (int i = 0; i < m_TextureIds.size(); i++)
	{
		Texture* texture = ResourceManager::GetInstance()->GetTexture(m_TextureIds.at(i));
		m_Textures.push_back(texture);
	}

	for (int i = 0; i < m_CubeTextureIds.size(); i++)
	{
		Texture* cubeTexture = ResourceManager::GetInstance()->GetCubeTexture(m_CubeTextureIds.at(i));
		m_Textures.push_back(cubeTexture);
	}

	m_Shaders = ResourceManager::GetInstance()->GetShaders(m_shadersId);
}

Object::Object(const char* modelPath, const char* texturePath)
{
	m_Model = new Model(modelPath);
	m_Texture = new Texture(texturePath);
	m_Shaders->Init("Shaders/TriangleShaderVS.vs", "Shaders/TriangleShaderFS.fs");

	m_Scale = Vector3(1, 1, 1);
	m_Rotation = Vector3(0, 0, 0);
	m_Translation = Vector3(0, 0, 0);
}

void Object::SetModelId(int id)
{
	m_modelId = id;
}

void Object::SetTranslation(Vector3 translation)
{
	m_Translation = translation;
}

void Object::SetTextureId(int id)
{
	//m_textureId = id;
	m_TextureIds.push_back(id);
}

void Object::SetTextureCubeId(int id)
{
	//m_textureCubeId = id;
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
	m_Rotation = rotation;
}

void Object::Draw()
{
	m_Model->BindBuffer();

	for (int i = 0; i < m_Textures.size(); i++)
	{
		m_Textures.at(i)->BindBuffer(i);
	}

	m_Shaders->Use(GetWVP());

	m_Model->Draw();

	m_Model->BindBuffer(false);
	//m_Texture->BindBuffer(false);
	for (int i = 0; i < m_Textures.size(); i++)
	{
		m_Textures.at(i)->BindBuffer(i, false);
	}
}

void Object::Update(float deltaTime)
{

}

Object::~Object()
{
	m_Model = NULL;
	m_Texture = NULL;
	m_Shaders = NULL;

	m_TextureIds.clear();
}
