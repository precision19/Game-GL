#pragma once
#include "PrefabManager.h"
#include "box2d/box2d.h"
#include "Player.h"
#include "TreasureChest.h"
#include "Physic.h"
#include "MenuState.h"
#include "MapState.h"
#include "LevelState.h"

class SceneManager : public StateManager
{
protected:
	static SceneManager* ms_Instance;
	//MyContactListener* myContactListenerInstance;
public:
	static void CreateInstance();
	static SceneManager* GetInstance();
	static void DestroyInstance();

	//vector<Object*> m_vObjects;

	SceneManager();
	//void LoadScene(string);
	//void AddPhysicsToScene();
	void Draw();
	void Update(float);
	//void DestroyAllObjects();
};

