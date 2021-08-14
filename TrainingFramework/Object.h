#pragma once
#include "../Utilities/utilities.h"
#include "Renderer2D.h"
#include "PrefabManager.h"
#include <map>

class Object
{
protected:
	string m_Name;
	Transform m_Transform;
	Renderer* m_Renderer;
public:
	Object();
	Object(string);
	virtual Object* Clone();

	void SetPosition(Vector3);
	void SetScale(Vector3);
	void SetRotation(Vector3);
	void SetRenderer(int);
	
	string GetName();
	Vector3 GetPosition();

	virtual void Draw();
	virtual void Update(float);

	virtual ~Object();
};

