#pragma once
#include "Object.h"

class EffectManager
{
protected:
	static EffectManager* s_Instance;
	//float time;
public:
	vector<Object*> o;
	static void CreateInstance();
	static void DestroyInstance();
	static EffectManager* GetInstance();
	EffectManager();
	~EffectManager();
	void Update(float);
	void MoveObject(Object*, Vector3, float, float);
};

