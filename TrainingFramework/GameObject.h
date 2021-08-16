#pragma once
#include "Box.h"
#include "Object.h"

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
	float GetCollider() { return m_ColliderSize; };
	virtual void CreateCollider();
	int GetID();
	Box* GetColliderBox() { return m_Collider; };
	virtual void OnColliderEnter(GameObject*);
	virtual void OnColliderExit(GameObject*);
	~GameObject();
};

