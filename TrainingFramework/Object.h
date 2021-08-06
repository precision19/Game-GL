#pragma once
#include "../Utilities/utilities.h"
#include "Renderer2D.h"
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
	Vector2 m_Dimension;

	Matrix GetWVP();

	vector<Component*> m_Components;

	int currentFrameId;
	float anim_cursor;
	float currentFrameTime;

	Renderer* m_Renderer;
public:
	Transform* transform;

	Object();
	void SetModel(int);
	void SetModel(string);
	void AddTexture(int);
	void AddTexture(string);
	void AddCubeTexture(int);
	void SetShaders(int);
	void SetShaders(string);

	void SetCurrentFrame(int);

	void SetNativeSize();

	void SetDimension(Vector2 dimen) { m_Dimension = dimen; }
	void SetPosition(Vector3);
	void SetScale(Vector3);
	void SetRotation(Vector3);

	Vector3 GetPosition();
	Vector2 GetDimension() { return m_Dimension; }

	void Draw();
	void Update(float);

	~Object();
};

