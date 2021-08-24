#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer()
{
	m_Model = NULL;
	m_Texture = NULL;
	m_Shaders = NULL;
	m_Opacity = 1.0;
}

Renderer::Renderer(string name)
{
	m_Name = name;
	m_Model = NULL;
	m_Texture = NULL;
	m_Shaders = NULL;
	m_Opacity = 1.0;
}

void Renderer::SetOpacity(float opacity)
{
	m_Opacity = opacity;
	if (m_Opacity < 0) m_Opacity = 0.0;
	if (m_Opacity > 1) m_Opacity = 1.0;
}

Renderer* Renderer::Clone()
{
	Renderer* result = new Renderer();
	result->m_Model = m_Model;
	result->m_Texture = m_Texture;
	result->m_Shaders = m_Shaders;
	return result;
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

string Renderer::GetName()
{
	return m_Name;
}

Vector3 Renderer::GetTextureSize()
{
	if (m_Texture == NULL)
	{
		printf("WARNING: Can't get size of null texture");
		return Vector3(1, 1, 1);
	}
	return m_Texture->GetSize();
}

void Renderer::Draw(Transform transform)
{
	if (m_Model == NULL || m_Shaders == NULL || m_Texture == NULL)
	{
		printf("WARNING: An object isn't renderered");
		return;
	}

	m_Model->BindBuffer();
	m_Texture->BindBuffer();
	glUseProgram(m_Shaders->program);

	if (m_Shaders->textureUniform != -1)
	{
		glUniform1i(m_Shaders->textureUniform, 0);
	}

	if (m_Shaders->opacityUniform != -1)
	{
		glUniform1f(m_Shaders->opacityUniform, m_Opacity);
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
		Matrix WVP = transform.GetWorldMatrix() * Camera::GetInstance()->GetViewMatrix() * Camera::GetInstance()->GetProjection();
		glUniformMatrix4fv(m_Shaders->WVPUniform, 1, GL_FALSE, &WVP.m[0][0]);
	}

	m_Model->Draw();

	m_Model->BindBuffer(false);
	m_Texture->BindBuffer(false);
}

void Renderer::Update(float deltaTime)
{
}

void Renderer::SetLoop(bool)
{
}

void Renderer::Reset()
{
	m_Opacity = 1.0;
}

Renderer::~Renderer()
{
	m_Model = NULL;
	m_Texture = NULL;
	m_Shaders = NULL;
}
