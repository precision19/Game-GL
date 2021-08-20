#pragma once
#include "GameObject.h"
#include "Box.h"

class SpinnerFly : public GameObject
{
protected:
	float m_speed;
	float m_radius;
	bool m_IsReset;
	float m_Time;
	float m_angle;
	Vector3 m_positionCenter;
	Vector3 m_rotate;
	bool vectorX;
public:
	SpinnerFly();
	SpinnerFly* Clone();
	void SetSpeed(float);
	void SetPositionCenter(Vector3);
	void SetRadius();

	void CreateCollider();
	void Update(float);

	void OnColliderEnter(GameObject*);
	void OnColliderExit(GameObject*);

	~SpinnerFly();
};
