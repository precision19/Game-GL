#pragma once
#include "Object.h"

struct MoveEffect {
	Object* object;
	Vector3 destination;
	float timeRemain;
};

struct FadedEffect {
	Object* object;
	float targetOpacity;
	float timeRemain;
};

struct AnimationEffect {
	Object* object;
	vector<pair<string, bool> >nameAnimation;
};

class EffectManager
{
protected:
	static EffectManager* s_Instance;
	vector<MoveEffect*>m_MoveEffects;
	vector<FadedEffect*>m_FadedEffects;
	vector<AnimationEffect*>m_AnimationEffects;
public:
	static void CreateInstance();
	static void DestroyInstance();
	static EffectManager* GetInstance();
	EffectManager();
	~EffectManager();

	void Draw();
	void Update(float);

	void AddMoveEffect(Object*, Vector3, float);
	void AddFadedEffect(Object*, float, float);
	void AddAnimationEffect(Object*, vector<string>&nameAnimation);

	void DestroyAllEffect();

	void MoveObject(Object*, Vector3, float, float);
	void Faded(Object*, float, float, float);//1 neu ro dan, 0 neu mo dan
	void LoadAnimation();
};
