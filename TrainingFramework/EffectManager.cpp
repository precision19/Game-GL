#include "stdafx.h"
#include "EffectManager.h"
#include "EventManager.h"

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
    float timeMove, timeFaded;
    int clearly;
    Vector3 destination;
    
    fscanf(f, "#Effects: %d\n", &amount);
    for (int i = 0; i < amount; i++)
    {
        fscanf(f, "ID %d\n", &id);

        Object* object = new Object();
        int numRender;
        fscanf(f, "RENDER %d\n", &numRender);
        m_NumRenders.push_back(numRender);
        for (int j = 0; j < numRender; j++) {
            fscanf(f, "RENDERER %s\n", name);
            if(j==0)object->SetRenderer(name);
            m_Animations.push_back({ name,i });
        }
        m_IndexAnimations.push_back(0);
        fscanf(f, "POSITION %f %f %f\n", &x, &y, &z);
        object->SetPosition(Vector3(x, y, z));
        fscanf(f, "ROTATION %f %f %f\n", &x, &y, &z);
        object->SetRotation(Vector3(x, y, z));
        fscanf(f, "SCALE %f %f %f\n", &x, &y, &z);
        object->SetScale(Vector3(x, y, z));
        fscanf(f, "DESTINATION %f %f %f\n", &x, &y, &z);
        destination = Vector3(x, y, z);
        fscanf(f, "TIMEMOVE %f\n", &timeMove);
        fscanf(f, "TIMEFADED %f\n", &timeFaded);
        fscanf(f, "CLEARLY %d\n", &clearly);
        if (clearly == 1) {
            object->GetRenderer()->SetOpacity(0.0f);
        }
        else {
            object->GetRenderer()->SetOpacity(1.0f);
        }
        AddEffect(object, destination, timeMove, timeFaded, clearly);
    }
}

void EffectManager::AddEffect(Object* object, Vector3 destination, float timeMove, float timeFaded, bool clearly) {
    m_objects.push_back(object);
    Effect* e = new Effect();
    e->destination = destination;
    e->timeFaded = timeFaded;
    e->timeMove = timeMove;
    e->clearly = clearly;
    m_effects.push_back(e);
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
    int count = 0;
    for (int i = 0; i < m_effects.size(); i++) {
        if (m_effects[i]->timeMove > 0) {
            MoveObject(m_objects[i], m_effects[i]->destination, m_effects[i]->timeMove, deltaTime);
            m_effects[i]->timeMove -= deltaTime;
            if (m_effects[i]->timeMove < 0)  m_effects[i]->timeMove = 0;
        }
        else count++;
        if (m_effects[i]->timeFaded > 0) {
            Faded(m_objects[i], m_effects[i]->timeFaded, deltaTime, m_effects[i]->clearly);
            m_effects[i]->timeFaded -= deltaTime;
            if (m_effects[i]->timeFaded < 0)  m_effects[i]->timeFaded = 0;
        }
        else count++;
    }
    LoadAnimation();
//    printf("%d\n", count);
    if (count == 2 * m_effects.size()) {
        EventManager::GetInstance()->InvokeEvent(EVENT_GROUP_GAMEPLAY, EVENT_EFFECT_DONE);
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

void EffectManager::LoadAnimation() {
    int tmp = -1;
    int indexObject = -1;
    for (int i = 0; i < m_Animations.size(); i++) {
        if (m_Animations[i].second != indexObject) {
            tmp = 0;
        }
        indexObject = m_Animations[i].second;
        if (m_IndexAnimations[indexObject] == tmp) {
            m_IndexAnimations[indexObject]++;
            m_IndexAnimations[indexObject] = m_IndexAnimations[indexObject] % m_NumRenders[indexObject];
            delete m_objects[indexObject]->GetRenderer();
            m_objects[indexObject]->SetRenderer(m_Animations[i].first);
            tmp = -100;
        }
        tmp++;
    }
}

void EffectManager::DestroyAllEffect() {
    for (int i = 0; i < m_effects.size(); i++) {
        delete m_effects[i];
        if (m_objects[i])delete m_objects[i];
    }
    m_effects.clear();
    m_objects.clear();
    int indexObject = -1;

}

EffectManager::~EffectManager() {
    DestroyAllEffect();
}