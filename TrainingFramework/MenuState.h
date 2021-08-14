#pragma once
#include "StateManager.h"
#include "Button.h"
#include "PrefabManager.h"

class MenuState : public StateBase 
{
protected:
	StateManager* m_StateManager;
	vector<Object*> m_Objects;
	//Button* m_PlayButton;
	//Button* m_SoundButton;
public:
	MenuState();
	void SetStateManager(StateManager*);
	void OnStart();
	void Update(float deltaTime);
	void Draw();
	~MenuState();
};