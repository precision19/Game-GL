#include "stdafx.h"
#include "MapState.h"


MapState::MapState() {
	Camera::CreateInstance();

	ResourceManager::CreateInstance();
	ResourceManager::GetInstance()->LoadResource("Map");

	PrefabManager::CreateInstance();
	PrefabManager::GetInstance()->LoadPrefabs("Map");

	SceneManager::CreateInstance();
	SceneManager::GetInstance()->LoadScene("Map");
	SceneManager::GetInstance()->AddPhysicsToScene();
}

void MapState::Update(float deltaTime) {
	Camera::GetInstance()->Update(deltaTime);
	SceneManager::GetInstance()->Update(deltaTime);
}

void MapState::Draw() {
	SceneManager::GetInstance()->Draw();
}

void MapState::Destroy() {
	Input::DestroyInstance();
	Camera::DestroyInstance();
	ResourceManager::DestroyInstance();
	PrefabManager::DestroyInstance();
	SceneManager::DestroyInstance();
}