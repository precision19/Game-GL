#pragma once
#include <vector>
#include "Object.h"
#include "Camera.h"
#include "ResourceManager.h"

class SceneManager
{
protected:
	static SceneManager* ms_Instance;
	std::vector<Object*> m_vObjects;
	int keyPressed = 0;
public:
	static void CreateInstance();
	static SceneManager* GetInstance();
	static void DestroyInstance();

	SceneManager();
	int Init();
	void KeyEventHandle(unsigned char, bool);
	void Draw();
	void Update(float);
	~SceneManager();
};

