#pragma once
#include "Object.h"
#include "EventManager.h"

struct Effect
{
	int eventInvokeId;
	bool isEnd;

	Effect() 
	{ 
		eventInvokeId = 0; 
		isEnd = false;
	}

	virtual void Update(float deltaTime) {}
	void OnFinish()
	{
		isEnd = true;
		if (eventInvokeId)
			EventManager::GetInstance()->InvokeEvent(EVENT_GROUP_EFFECT, eventInvokeId);
	}
};

struct MoveEffect : Effect 
{
	Object* object;
	Vector3 destination;
	float timeRemain;

	void Update(float deltaTime)
	{
		if (timeRemain <= deltaTime) 
		{
			object->SetPosition(Vector3(destination.x, destination.y, object->GetPosition().z));
			OnFinish();
			return;
		}
		Vector3 speed = (destination - object->GetPosition()) / timeRemain;
		object->SetPosition(object->GetPosition() + speed * deltaTime);
		timeRemain -= deltaTime;
	}
};

struct FadedEffect : Effect
{
	Object* object;
	float targetOpacity;
	float timeRemain;

	void Update(float deltaTime)
	{
		if (timeRemain <= deltaTime) 
		{
			object->GetRenderer()->SetOpacity(targetOpacity);
			OnFinish();
			return;
		}
		float opacity = object->GetRenderer()->GetOpacity();
		float speed = (targetOpacity - opacity) / timeRemain;
		object->GetRenderer()->SetOpacity(opacity + speed * deltaTime);
		timeRemain -= deltaTime;
	}
};

struct AnimationEffect : Effect
{
	Animation2D* animation;
	Vector3 position;

	void Update(float deltaTime)
	{
		if (animation->End())
		{
			OnFinish();
			return;
		}
		animation->Update(deltaTime);
	}
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
	void AddMoveEffect(Object*, Vector3, float, int);
	void AddFadedEffect(Object*, float, float);
	void AddFadedEffect(Object*, float, float, int);
	void AddAnimationEffect(Animation2D*, Vector3);
	void AddAnimationEffect(Animation2D*, Vector3, int);

	void DestroyAllEffect();
};
