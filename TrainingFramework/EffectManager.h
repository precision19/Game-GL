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
	vector<pair<string, int> > m_Animations;
	vector<int>m_IndexAnimations;
	vector<int>m_NumRenders;
	//float time;
public:
	static void CreateInstance();
	static void DestroyInstance();
	static EffectManager* GetInstance();
	EffectManager();
	~EffectManager();

	void Draw();
	void Update(float);
	void AddEffect(Object*, Vector3, float, float, bool);
	void LoadAnimation();
	void DestroyAllEffect();

	void MoveObject(Object*, Vector3, float, float);
	void Faded(Object*, float, float, bool);//1 neu ro dan, 0 neu mo dan
};
