#pragma once
#include <vector>
#include "Object.h"
#include "Camera.h"
#include "PrefabManager.h"
#include "box2d/box2d.h"
#include "Box.h"
#include "GroundBox.h"
#include "DynamicBox.h"
#include "Player.h"
#include "TreasureChest.h"
#include "MyContactListener.h"


class SceneManager
{
protected:
	static SceneManager* ms_Instance;
	MyContactListener* myContactListenerInstance;
	std::vector<Box*>m_boxes;
public:
	bool jumpPressed = 0;
	static void CreateInstance();
	static SceneManager* GetInstance();
	static void DestroyInstance();

	vector<Object*> m_vObjects;
	std::unique_ptr<b2World>m_world;

	SceneManager();
	void LoadScene(string);
	void AddPhysicsToScene();

	void Draw();
	void Update(float);
	void Jump();
	void DestroyAllObjects();
	~SceneManager();
};

