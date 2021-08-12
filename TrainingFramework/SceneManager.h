#pragma once
#include "PrefabManager.h"
#include "box2d/box2d.h"
#include "Player.h"
#include "TreasureChest.h"
#include "Physic.h"
#include "MenuState.h"
#include "MapState.h"
#include "LevelState.h"

class SceneManager
{
protected:
	static SceneManager* ms_Instance;
	MyContactListener* myContactListenerInstance;
	StateManager* m_StateManager;
public:
	static void CreateInstance();
	static SceneManager* GetInstance();
	static void DestroyInstance();

	vector<Object*> m_vObjects;

	SceneManager();
	void LoadScene(string);
	void AddPhysicsToScene();
	void Draw();
	void Update(float);
	void DestroyAllObjects();
	~SceneManager();
};

