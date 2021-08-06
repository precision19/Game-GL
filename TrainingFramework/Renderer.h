#pragma once
#include "ResourceManager.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"
#include "Transform.h"

class Renderer
{
protected:
	Model* m_Model;
	Texture* m_Texture;
	Shaders* m_Shaders;
	float m_FramePerSec;
public:
	Transform* transform;
	void SetTransform(Transform*);
	Renderer();
	void SetModel(int);
	void SetModel(string);
	virtual void SetTexture(int);
	virtual void SetTexture(string);
	void SetFramePerSec(int);
	void SetShaders(int);
	void SetShaders(string);
	virtual Vector3 GetSize();
	virtual Matrix GetWVP();
	void Draw();
	virtual void Update(float);
	virtual ~Renderer();
};

