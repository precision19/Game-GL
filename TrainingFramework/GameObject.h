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
	virtual void Reset();
	void SetCollider(float);
	float GetCollider() { return m_ColliderSize; };
	Box* GetColliderBox() { return m_Collider; };
	void SetColliderBox(Box* box) { m_Collider = box; };
	virtual void CreateCollider();
	int GetID();
	
	// only Guard
	virtual void SetPositionStart(Vector3);
	virtual void SetPositionEnd(Vector3);

	virtual void OnColliderEnter(GameObject*);
	virtual void OnColliderExit(GameObject*);
	virtual ~GameObject();
};

