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
    //time = 3;
}

void EffectManager::MoveObject(Object* object, Vector3 destination, float time, float deltaTime) {
    if (time <= deltaTime) {
        object->SetPosition(Vector3(destination.x, destination.y, object->GetPosition().z));
        return;
    }
    Vector3 speed = (destination - object->GetPosition()) / time;
    object->SetPosition(object->GetPosition() + speed*deltaTime);
}

void EffectManager::Update(float deltaTime) {
    /*for (int i = 0; i < o.size(); i++) {
        MoveObject(o[i], Vector3(0.0f, 0.0f, 0.0f), time, deltaTime);
        Faded(o[i], time, deltaTime, 1);
    }
    time -= deltaTime;
    if (time < 0) time = 0;*/
}

void EffectManager::Faded(Object* object, float time, float deltaTime, bool clearly) {
    if (time <= deltaTime) {
        object->GetRenderer()->SetOpacity((float)clearly);
        return;
    }
    float opacity = object->GetRenderer()->GetOpacity();
    if (clearly) {
        float speed = (1.0f - opacity) / time;
        object->GetRenderer()->SetOpacity(opacity + speed * deltaTime);
    }
    else {
        float speed = opacity / time;
        object->GetRenderer()->SetOpacity(opacity - speed * deltaTime);
    }
    //printf("%f\n", opacity);
}

EffectManager::~EffectManager() {

}
