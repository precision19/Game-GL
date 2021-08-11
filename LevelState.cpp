#include "stdafx.h"
#include "LevelState.h"


LevelState::LevelState() {
	Camera::CreateInstance();

	ResourceManager::CreateInstance();
	ResourceManager::GetInstance()->LoadResource("Level1");

	PrefabManager::CreateInstance();
	PrefabManager::GetInstance()->LoadPrefabs("Level1");

	SceneManager::CreateInstance();
	SceneManager::GetInstance()->LoadScene("Level1");
	SceneManager::GetInstance()->AddPhysicsToScene();
}

void LevelState::Update(float deltaTime) {
	Camera::GetInstance()->Update(deltaTime);
	SceneManager::GetInstance()->Update(deltaTime);
}

void LevelState::Draw() {
	SceneManager::GetInstance()->Draw();
}

void LevelState::Destroy() {
	Input::DestroyInstance();
	Camera::DestroyInstance();
	ResourceManager::DestroyInstance();
	PrefabManager::DestroyInstance();
	SceneManager::DestroyInstance();
}