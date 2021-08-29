#pragma once
#include "EffectManager.h"
#include "StateManager.h"
#include "Button.h"
#include "PrefabManager.h"
#include "AudioManager.h"

class MenuState : public StateBase 
{
protected:
	bool m_IsFirst;
	StateManager* m_StateManager;
	vector<Object*> m_Objects;
	Object* m_Logo;
public:
	MenuState();
	void SetStateManager(StateManager*);
	void OnStart();
	void Update(float deltaTime);
	void Draw();
	~MenuState();
};