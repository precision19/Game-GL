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
    string path = "Managers/EM.txt";
    FILE* f = fopen(path.c_str(), "r+");
    if (f == NULL)
    {
        printf("Invalid file %s\n", path.c_str());
        exit(1);
    }
    int amount, id;
    float x, y, z;
    char name[20];

    
    fscanf(f, "#Effects: %d\n", &amount);
    for (int i = 0; i < amount; i++)
    {
        fscanf(f, "ID %d\n", &id);

        Effect* effect = new Effect();
        Object* object = new Object();
        
        fscanf(f, "RENDERER %s\n", name);
        object->SetRenderer(name);
        fscanf(f, "POSITION %f %f %f\n", &x, &y, &z);
        object->SetPosition(Vector3(x, y, z));
        fscanf(f, "ROTATION %f %f %f\n", &x, &y, &z);
        object->SetRotation(Vector3(x, y, z));
        fscanf(f, "SCALE %f %f %f\n", &x, &y, &z);
        object->SetScale(Vector3(x, y, z));
        fscanf(f, "DESTINATION %f %f %f\n", &x, &y, &z);
        effect->destination = Vector3(x, y, z);
        fscanf(f, "TIMEMOVE %f\n", &effect->timeMove);
        fscanf(f, "TIMEFADED %f\n", &effect->timeFaded);
        fscanf(f, "CLEARLY %d\n", &effect->clearly);
        if (effect->clearly == 1) {
            object->GetRenderer()->SetOpacity(0.0f);
        }
        else {
            object->GetRenderer()->SetOpacity(1.0f);
        }
        m_objects.push_back(object);
        m_effects.push_back(effect);
    }
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
    for (int i = 0; i < m_effects.size(); i++) {
        if (m_effects[i]->timeMove >= 0) {
            MoveObject(m_objects[i], m_effects[i]->destination, m_effects[i]->timeMove, deltaTime);
            m_effects[i]->timeMove -= deltaTime;
            if (m_effects[i]->timeMove < 0)  m_effects[i]->timeMove = 0;
        }
        if (m_effects[i]->timeFaded >= 0) {
            Faded(m_objects[i], m_effects[i]->timeFaded, deltaTime, m_effects[i]->clearly);
            m_effects[i]->timeFaded -= deltaTime;
            if (m_effects[i]->timeFaded < 0)  m_effects[i]->timeFaded = 0;
        }
    }
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

void EffectManager::Draw() {
    for (int i = 0; i < m_objects.size(); i++) {
        if (m_objects[i] != NULL) {
            m_objects[i]->Draw();
        }
    }
}

EffectManager::~EffectManager() {
    for (int i = 0; i < m_effects.size(); i++) {
        delete m_effects[i];
        delete m_objects[i];
    }
}