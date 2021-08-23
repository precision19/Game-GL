#pragma once
#include "../Utilities/utilities.h"
#include "Renderer2D.h"
#include "PrefabManager.h"
#include <map>
#include "FlagManager.h"

class Object
{
protected:

	Transform m_Transform;
	Renderer* m_Renderer;
public:
	string m_Name;
	Object();
	Object(string);
	virtual Object* Clone();

	virtual void SetPosition(Vector3);
	void SetScale(Vector3);
	void SetRotation(Vector3);
	virtual void SetRenderer(int);
	virtual void SetRenderer(string);
	
	string GetName();
	Vector3 GetPosition();
	Renderer* GetRenderere();

	Renderer* GetRenderer();

	virtual void Draw();
	virtual void Update(float);

	virtual ~Object();
};

