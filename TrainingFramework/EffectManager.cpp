#include "stdafx.h"
#include "EffectManager.h"

EffectManager* EffectManager::s_Instance = NULL;

void EffectManager::CreateInstance()
{
    if (s_Instance == NULL)
        s_Instance = new EffectManager();
}

EffectManager* EffectManager::GetInstance()
{
    return s_Instance;
}

void EffectManager::DestroyInstance()
{
    if (s_Instance)
    {
        delete s_Instance;
        s_Instance = NULL;
    }
}

EffectManager::EffectManager() {
    //time = 1.5;
}

void EffectManager::MoveObject(Object* object, Vector3 destination, float time, float deltaTime) {
    if (time <= 0) return;
    float speedX = (destination.x - object->GetPosition().x) / time;
    float speedY = (destination.y - object->GetPosition().y) / time;
    float newPositionX = object->GetPosition().x + speedX * deltaTime;
    float newPositionY = object->GetPosition().y + speedX * deltaTime;
    object->SetPosition(Vector3(newPositionX, newPositionY, object->GetPosition().z));
}

void EffectManager::Update(float deltaTime) {
    /*for (int i = 0; i < o.size(); i++) {
        MoveObject(o[i], Vector3(0.0f, 0.0f, 0.0f), time, deltaTime);
    }
    time -= deltaTime;
    if (time < 0) time = 0;*/
}

EffectManager::~EffectManager() {

}
