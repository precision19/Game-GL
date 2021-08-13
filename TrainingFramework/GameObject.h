#pragma once
#include "DynamicBox.h"
#include "GroundBox.h"

class GameObject :
    public Object
{
protected:
	static int ms_IDMaker;

	int m_ID;
	Box* m_Collider;
	float m_ColliderSize;
public:
	GameObject();
	GameObject(string);
	virtual Object* Clone();
	void SetCollider(float);
	virtual void CreateCollider();
	int GetID();
	virtual void OnColliderEnter(GameObject*);
	virtual void OnColliderExit(GameObject*);
};

