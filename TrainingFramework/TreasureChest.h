#pragma once
#include "GameObject.h"
#include "DynamicBox.h"

class TreasureChest : public GameObject
{
public:
	bool isWinner;
	vector<Renderer* > m_Animations;

	TreasureChest();
	~TreasureChest();

	bool isCollistion();
	void AddAnimations(Renderer*);

	void CreateCollider();
	void Draw();
	void Update(float);

	void OnColliderEnter(GameObject*);
	void OnColliderExit(GameObject*);
};

