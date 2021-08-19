#pragma once
#include "GameObject.h"
#include "Sensor.h";
#include "AudioManager.h"

class Player : public GameObject
{
protected:
	bool m_Enable;
	bool m_IsRunning;
	int canJump;
	vector<Renderer*> m_Animations;
	int m_currentAnimationId;
	float m_SpeedX;
	float m_JumpForce;
	float m_SlideSpeed;
	int canSlide;
	bool onTheGround;
	Sensor* foot, * right, * left;
	bool m_IsFacingRight;
	Vector3 m_GatePosition;
	bool m_IsReset;
public:
	Player();
	void CreateCollider();
	void CreateSensorCollider();
	void Reset();
	void SetSpeed(float);
	void SetJumpForce(float);
	void SetRenderer(string);

	void Update(float);
	void UpdateSensorOfPlayer(float);
	void UpdateAnimation(float);
	void ConsiderJumpAndSlide();
	void HandleJumpAndSlide();
	void Stop();
	void Die();
	void SetJump(int jump) { canJump = jump; };
	int GetJump() { return canJump; };

	void OnColliderEnter(GameObject*);
	void OnColliderExit(GameObject*);

	~Player();
};

