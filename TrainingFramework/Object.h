#pragma once
#include "../Utilities/utilities.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "Component.h"

class Object
{
protected:
	Model* m_Model;
	vector<Texture*> m_Textures;
	Shaders* m_Shaders;

	Vector3 m_Scale;
	Vector3 m_Rotation;
	Vector3 m_Position;

	Matrix GetWVP();

	vector<Component*> m_Components;
public:
	Transform* transform;

	Object();
	void SetModel(int);
	void SetModel(string);
	void AddTexture(int);
	void AddTexture(string);
	void AddCubeTexture(int);
	void SetShaders(int);
	void SetSahders(string);

	void SetNativeSize();

	void SetPosition(Vector3);
	void SetScale(Vector3);
	void SetRotation(Vector3);

	Vector3 GetPosition();

	void Draw();
	void Update(float);

	~Object();
};

