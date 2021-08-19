#pragma once
#include "GameObject.h"
#include "DynamicBox.h"
#include "AudioManager.h"

class TreasureChest : public GameObject
{
public:

	int m_currentAnimation;
	bool isWinner;
	vector<Renderer* > m_Animations;

	TreasureChest();
	~TreasureChest();

	bool isCollistion();
	void AddAnimations(Renderer*);
	void SetRenderer(int);
	void SetRenderer(string);

	void CreateCollider();
	void Draw();
	void Update(float);

	void OnColliderEnter(GameObject*);
	void OnColliderExit(GameObject*);
};

