#include "stdafx.h"
#include "StateManager.h"

StateManager::StateManager() {
	this->state = new MenuState();
}

void StateManager::Update(float deltaTime) {
	this->state->Update(deltaTime);
}

void StateManager::Draw() {
	this->state->Draw();
}

void StateManager::Destroy() {
	this->state->Destroy();
}