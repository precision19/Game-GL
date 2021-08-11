#include "stdafx.h"
#include "MenuState.h"

MenuState::MenuState() {
	Camera::CreateInstance();

	ResourceManager::CreateInstance();
	ResourceManager::GetInstance()->LoadResource("Menu");

	PrefabManager::CreateInstance();
	PrefabManager::GetInstance()->LoadPrefabs("Menu");

	SceneManager::CreateInstance();
	SceneManager::GetInstance()->LoadScene("Menu");
	SceneManager::GetInstance()->AddPhysicsToScene();
}

void MenuState::Update(float deltaTime) {
	Camera::GetInstance()->Update(deltaTime);
	SceneManager::GetInstance()->Update(deltaTime);
}

void MenuState::Draw() {
	SceneManager::GetInstance()->Draw();
}

void MenuState::Destroy() {
	Input::DestroyInstance();
	Camera::DestroyInstance();
	ResourceManager::DestroyInstance();
	PrefabManager::DestroyInstance();
	SceneManager::DestroyInstance();
}