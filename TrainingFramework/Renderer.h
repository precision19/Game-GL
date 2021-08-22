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
	string m_Name;
	Model* m_Model;
	Texture* m_Texture;
	Shaders* m_Shaders;
	float m_Opacity;
public:
	Renderer();
	Renderer(string);
	void SetOpacity(float);
	float GetOpacity() { return m_Opacity; };
	virtual Renderer* Clone();
	void SetModel(int);
	void SetModel(string);
	virtual void SetTexture(int);
	virtual void SetTexture(string);
	void SetShaders(int);
	void SetShaders(string);
	string GetName();
	Vector3 GetTextureSize();
	virtual void Draw(Transform);
	virtual void Update(float);
	virtual void SetLoop(bool);
	virtual ~Renderer();
};

