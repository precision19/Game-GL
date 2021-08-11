#pragma once
#include <vector>
#include "Object.h"
#include "Camera.h"
#include "PrefabManager.h"
#include "box2d/box2d.h"
#include "Player.h"
#include "TreasureChest.h"
#include "Physic.h"


class SceneManager
{
protected:
	static SceneManager* ms_Instance;
	MyContactListener* myContactListenerInstance;
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

