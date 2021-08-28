#pragma once

#include "GameObject.h"
#include "Physic.h"

class Bullet : public GameObject
{
protected:
	bool m_IsRender;
	float m_speed;
	Vector2 m_VectorSpeed;
	Vector3 m_BasePosition;
public:
	Bullet();

	void Draw();
	Bullet* Clone();
	void SetSpeed(float);
	void CreateCollider();
	void Update(float);
	void SetIsRender(bool isRender) { m_IsRender = isRender; }
	bool GetIsRender() { return m_IsRender; }
	void SetVectorSpeed(Vector2 vtsp) { m_VectorSpeed = vtsp; }
	Vector2 GetVectorSpeed() { return m_VectorSpeed; }
	void SetBasePosition(Vector3 bp) { m_BasePosition = bp; }
	Vector3 GetBasePosition() { return m_BasePosition; }
	void OnColliderEnter(GameObject*);
	void OnColliderExit(GameObject*);
	~Bullet();
};

