#pragma once
#include "../Utilities/utilities.h"
#include "Renderer2D.h"
#include "PrefabManager.h"

class Object
{
protected:
	Vector2 m_Dimension;
	Transform transform;
	Renderer* m_Renderer;
public:
	char type[10];
	Object();
	void SetDimension(Vector2 dimen) { m_Dimension = dimen; }
	void SetPosition(Vector3);
	void SetScale(Vector3);
	void SetRotation(Vector3);
	void SetRenderer(int);
	void SetNativeSize();
	Vector3 GetPosition();
	Vector2 GetDimension() { return m_Dimension; }

	void Draw();
	void Update(float);

	~Object();
};

