#pragma once
#include "Box.h"
#include "Object.h"

#define PLAYER "Player"
#define TREASURE_CHEST "TreasureChest"
#define GATE "Gate"
#define BLOCK "Block"
#define BLOCK_L "Block_L"
#define BLOCK_L_UP "Block_L_Up"
#define BLOCK_R "Block_R"
#define BLOCK_R_UP "Block_R_Up"
#define SOIL1 "Soil1"
#define SOIL3 "Soil3"
#define BLOCK_DOWN "Block_Down"
#define STAR "Star"
#define BULLET "Bullet"
#define GUN "Gun"
#define GUARD "Guard"
#define SPINNER "Spinner"
#define SAW_BLADE "SawBlade"
#define CHASER "Chaser"


class GameObject :
    public Object
{
protected:
	static int ms_IDMaker;

	int m_ID;
	Box* m_Collider;
	float m_ColliderSize;
	Vector3 m_ResetPosition;
public:
	GameObject();
	GameObject(string);
	virtual Object* Clone();
	virtual void Reset();

	void SetPosition(Vector3);
	void SetCollider(float);
	void SetColliderBox(Box* box) { m_Collider = box; };
	
	virtual void CreateCollider();

	int GetID();
	float GetCollider() { return m_ColliderSize; };
	Box* GetColliderBox() { return m_Collider; };

	virtual void SetPositionStart(Vector3);
	virtual void SetPositionEnd(Vector3);

	virtual void OnColliderEnter(GameObject*);
	virtual void OnColliderExit(GameObject*);

	virtual void DestroyCollider();
	virtual ~GameObject();
};

