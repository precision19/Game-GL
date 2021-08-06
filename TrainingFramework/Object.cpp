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
	transform = new Transform();
	transform->position = Vector3(0, 0, 0);
	transform->rotation = Vector3(0, 0, 0);
	transform->scale = Vector3(1, 1, 1);
	m_Model = NULL;
	m_Shaders = NULL;
	currentFrameTime = 0.3;
	anim_cursor = 0;
	currentFrameId = NULL;
	m_Renderer = new Renderer2D();
	m_Renderer->SetTransform(transform);
}

void Object::SetNativeSize()
{
	//Vector2 size = m_Textures[0]->GetSize();
	//m_Scale = Vector3(size.x, size.y, 1);
	//m_Dimension = size;
	Vector3 size = m_Renderer->GetSize();
	m_Dimension = Vector2(size.x, size.y);
	printf("%f %f\n", m_Dimension.x, m_Dimension.y);
}

void Object::SetModel(int modelID)
{
	m_Model = ResourceManager::GetInstance()->GetModel(modelID);
	m_Renderer->SetModel(modelID);
}

void Object::SetModel(string modelName)
{
	m_Model = ResourceManager::GetInstance()->GetModel(modelName);
}

void Object::AddTexture(int textureID)
{
	m_Textures.push_back(ResourceManager::GetInstance()->GetTexture(textureID));
	m_Renderer->SetTexture(textureID);
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
	m_Renderer->SetShaders(shadersID);
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
	transform->position = position;
}

void Object::Draw()
{
	/*anim_cursor += currentFrameTime;
	if (m_Model == NULL || m_Shaders == NULL)
		return;

	m_Model->Model::BindBuffer();
	m_Textures.at(currentFrameId)->BindBuffer(0, TRUE);

	m_Shaders->UseState();

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

	m_Model->Model::Draw();

	m_Model->Model::BindBuffer(false);
	m_Textures.at(currentFrameId)->BindBuffer(currentFrameId, FALSE);*/
	m_Renderer->Draw();
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
	m_Renderer->Update(deltaTime);
}

Object::~Object()
{
	m_Model = NULL;
	m_Textures.clear();
	m_Shaders = NULL;
	delete transform;
	delete m_Renderer;
}
