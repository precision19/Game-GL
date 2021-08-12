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

public:
	Renderer();
	virtual Renderer* Clone();
	void SetModel(int);
	void SetModel(string);
	virtual void SetTexture(int);
	virtual void SetTexture(string);
	void SetShaders(int);
	void SetShaders(string);
	Vector3 GetTextureSize();
	virtual void Draw(Transform);
	virtual void Update(float);
	virtual ~Renderer();
};

