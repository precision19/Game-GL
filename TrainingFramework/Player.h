#pragma once
#include "GameObject.h"
#include "Sensor.h";

class Player : public GameObject
{
protected:
	int canJump;
	vector<Renderer*> m_Animations;
	int m_currentAnimationId;
	float m_SpeedX;
	float m_JumpForce;
public:
	Sensor* foot, *right, *left;

	float surfTime;
	int canSurf;
	bool surf;
	Player();
	void CreateCollider();
	void CreateSensorCollider();

	void SetSpeed(float);
	void SetJumpForce(float);
	void AddAnimation(Renderer*);

	void Update(float);
	void UpdateSensorOfPlayer(float);
	void ConsiderJumpingAndSurfing();

	void SetJump(int jump) { canJump = jump; };
	int GetJump() { return canJump; };

	void OnColliderEnter(GameObject*);
	void OnColliderExit(GameObject*);

	~Player();
};

