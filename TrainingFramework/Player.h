#pragma once
#include "GameObject.h"

class Player : public GameObject
{
protected:
	int canJump;
	vector<Renderer*> m_Animations;
	int m_currentAnimationId;
	float m_Speed;
	float m_JumpForce;
public:
	float veloX;
	int canSurf;
	bool surf;
	Player();
	void CreateCollider();
	void SetSpeed(float);
	void SetJumpForce(float);
	void AddAnimation(Renderer*);
	void Update(float);
	void SetJump(int jump) { canJump = jump; };
	int GetJump() { return canJump; };

	void OnColliderEnter(GameObject*);
	void OnColliderExit(GameObject*);

	~Player();
};

