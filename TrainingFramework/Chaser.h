#pragma once
#include "GameObject.h"
class Chaser : public GameObject
{
protected:
	Vector2 m_speed;
	Vector3 m_positionStart;
	Vector2 m_positionTarget;
	float m_maxSpeed;
	bool m_IsReset;
public:
	Chaser();
	Chaser* Clone();
	void SetSpeed(float);
	void SetPositionStart(Vector3);
	void SetPositionTarget(Vector2 target) { m_positionTarget = target; };

	void CreateCollider();
	void Update(float);

	void OnColliderEnter(GameObject*);
	void OnColliderExit(GameObject*);

	void Reset();
	~Chaser();

};

