#include "stdafx.h"
#include "Renderer2D.h"

Renderer2D::Renderer2D()
{
	m_Name = "Renderer 2D";
	m_Model = NULL;
	m_Texture = NULL;
	m_Shaders = NULL;
	m_Opacity = 1.0;
}

Renderer2D::Renderer2D(string name)
{
	m_Name = name;
	m_Model = NULL;
	m_Texture = NULL;
	m_Shaders = NULL;
	m_Opacity = 1.0;
}

Renderer* Renderer2D::Clone()
{
	Renderer2D* result = new Renderer2D();
	result->m_Model = m_Model;
	result->m_Texture = m_Texture;
	result->m_Shaders = m_Shaders;
	return result;
}

void Renderer2D::Draw(Transform transform)
{
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
		Matrix WVP = transform.GetWorldMatrix(m_Texture->GetSize()) * Camera::GetInstance()->GetViewMatrix() * Camera::GetInstance()->GetProjection();
		glUniformMatrix4fv(m_Shaders->WVPUniform, 1, GL_FALSE, &WVP.m[0][0]);
	}

	m_Model->Draw();

	m_Model->BindBuffer(false);
	m_Texture->BindBuffer(false);
}

Renderer2D::~Renderer2D()
{
	
}
