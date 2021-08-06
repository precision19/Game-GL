#include "stdafx.h"
#include "Renderer.h"

void Renderer::SetTransform(Transform* objectTransform)
{
	transform = objectTransform;
}

Renderer::Renderer()
{
	m_Model = NULL;
	m_Texture = NULL;
	m_Shaders = NULL;
}

void Renderer::SetModel(int id)
{
	m_Model = ResourceManager::GetInstance()->GetModel(id);
}

void Renderer::SetModel(string name)
{
	m_Model = ResourceManager::GetInstance()->GetModel(name);
}

void Renderer::SetTexture(int id)
{
	m_Texture = ResourceManager::GetInstance()->GetTexture(id);
}

void Renderer::SetTexture(string name)
{
	m_Texture = ResourceManager::GetInstance()->GetTexture(name);
}

void Renderer::SetShaders(int id)
{
	m_Shaders = ResourceManager::GetInstance()->GetShaders(id);
}

void Renderer::SetShaders(string name)
{
	m_Shaders = ResourceManager::GetInstance()->GetShaders(name);
}

Vector3 Renderer::GetSize()
{
	return transform->scale;
}

Matrix Renderer::GetWVP()
{
	Matrix WVP = transform->GetWorldMatrix() * Camera::GetInstance()->GetViewMatrix() * Camera::GetInstance()->GetProjection();
	return WVP;
}

void Renderer::Draw()
{
	m_Model->BindBuffer();
	m_Texture->BindBuffer();
	glUseProgram(m_Shaders->program);

	if (m_Shaders->textureUniform != -1)
	{
		glUniform1i(m_Shaders->textureUniform, 0);
	}

	if (m_Shaders->positionAttribute != -1)
	{
		glEnableVertexAttribArray(m_Shaders->positionAttribute);
		glVertexAttribPointer(m_Shaders->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (m_Shaders->uvAttribute != -1)
	{
		glEnableVertexAttribArray(m_Shaders->uvAttribute);
		glVertexAttribPointer(m_Shaders->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)sizeof(Vector3));
	}

	if (m_Shaders->WVPUniform != -1)
	{
		glUniformMatrix4fv(m_Shaders->WVPUniform, 1, GL_FALSE, &GetWVP().m[0][0]);
	}

	m_Model->Draw();

	m_Model->BindBuffer(false);
	m_Texture->BindBuffer(false);
}

void Renderer::Update(float deltaTime)
{
}

Renderer::~Renderer()
{
	m_Model = NULL;
	m_Texture = NULL;
	m_Shaders = NULL;
}
