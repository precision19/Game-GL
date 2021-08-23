#pragma once
#include "Object.h"

struct Effect {
	Vector3 destination;
	float timeMove;
	float timeFaded;
	bool clearly;
};

class EffectManager
{
protected:
	static EffectManager* s_Instance;
	vector<Effect*>m_effects;
	vector<Object*>m_objects;
	//float time;
public:
	static void CreateInstance();
	static void DestroyInstance();
	static EffectManager* GetInstance();
	EffectManager();
	~EffectManager();

	void Draw();
	void Update(float);

	void MoveObject(Object*, Vector3, float, float);
	void Faded(Object*, float, float, bool);//1 neu ro dan, 0 neu mo dan
};
