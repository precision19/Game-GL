#pragma once
#include "../Utilities/utilities.h"
#include "Renderer2D.h"
#include "PrefabManager.h"
#include <map>

enum Type
{
	GROUND,
	PLAYER,
	NONE,
	SENSOR
};

class Object
{
protected:
	string m_Name;
	int ID;
	Vector2 m_Dimension;
	Transform m_Transform;
	Renderer* m_Renderer;
	
public:
	Type type;
	Object();
	Object(string);
	virtual Object* Clone();
	void SetDimension(Vector2 dimen) { m_Dimension = dimen; }
	void SetPosition(Vector3);
	void SetScale(Vector3);
	void SetRotation(Vector3);
	void SetRenderer(int);
	void SetNativeSize(int);
	
	Vector3 GetPosition();
	Vector2 GetDimension() { return m_Dimension; }

	virtual void Draw();
	virtual void Update(float);

	int GetID() { return ID; };
	void SetID(int objID) { ID = objID; };

	virtual ~Object();
};

