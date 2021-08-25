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
    
}

void EffectManager::AddMoveEffect(Object* object, Vector3 destination, float timeRemain) {
    MoveEffect* me = new MoveEffect();
    me->object = object;
    me->destination = destination;
    me->timeRemain = timeRemain;
    m_MoveEffects.push_back(me);
}

void EffectManager::AddFadedEffect(Object* object, float targetOpacity, float timeRemain) {
    FadedEffect* fe = new FadedEffect();
    fe->object = object;
    fe->targetOpacity = targetOpacity;
    fe->timeRemain = timeRemain;
    m_FadedEffects.push_back(fe);
}

void EffectManager::AddAnimationEffect(Object* object, vector<string>& nameAnimation) {
    AnimationEffect* ae = new AnimationEffect();
    ae->object = object;
    for (int i = 0; i < nameAnimation.size(); i++) {
        ae->nameAnimation.push_back({ nameAnimation[i], 0 });
    }
    m_AnimationEffects.push_back(ae);
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
    //int count = 0;
    for (int i = 0; i < m_MoveEffects.size(); i++) {
        if (m_MoveEffects[i]->timeRemain > 0) {
            MoveObject(m_MoveEffects[i]->object, m_MoveEffects[i]->destination, m_MoveEffects[i]->timeRemain, deltaTime);
            m_MoveEffects[i]->timeRemain -= deltaTime;
            if (m_MoveEffects[i]->timeRemain < 0)  m_MoveEffects[i]->timeRemain = 0;
        }
        //else count++;
    }
    for(int i=0; i<m_FadedEffects.size(); i++){
        if (m_FadedEffects[i]->timeRemain > 0) {
            Faded(m_FadedEffects[i]->object, m_FadedEffects[i]->timeRemain, deltaTime, m_FadedEffects[i]->targetOpacity);
            m_FadedEffects[i]->timeRemain -= deltaTime;
            if (m_FadedEffects[i]->timeRemain < 0)  m_FadedEffects[i]->timeRemain = 0;
        }
        //else count++;
    }
    LoadAnimation();
//    printf("%d\n", count);
    /*if (count == 2 * m_MoveEffects.size()) {
        EventManager::GetInstance()->InvokeEvent(EVENT_GROUP_GAMEPLAY, EVENT_EFFECT_DONE);
    }*/
}

void EffectManager::Faded(Object* object, float time, float deltaTime, float targetOpacity) {
    if (time <= deltaTime) {
        object->GetRenderer()->SetOpacity((float)targetOpacity);
        return;
    }
    float opacity = object->GetRenderer()->GetOpacity();
    float speed = (targetOpacity - opacity) / time;
    object->GetRenderer()->SetOpacity(opacity + speed * deltaTime);
}

void EffectManager::Draw() {
    //("%d %d %d\n", m_AnimationEffects.size(), m_FadedEffects.size(), m_MoveEffects.size());
    for (int i = 0; i < m_MoveEffects.size(); i++) {
        if (m_MoveEffects[i]->object != NULL) {
            m_MoveEffects[i]->object->Draw();
        }
    }
    for (int i = 0; i < m_FadedEffects.size(); i++) {
        if (m_FadedEffects[i]->object != NULL) {
            m_FadedEffects[i]->object->Draw();
        }
    }
    for (int i = 0; i < m_AnimationEffects.size(); i++) {
        if (m_AnimationEffects[i]->object != NULL) {
            m_AnimationEffects[i]->object->Draw();
        }
    }
}

void EffectManager::LoadAnimation() {
    for (int i = 0; i < m_AnimationEffects.size(); i++) {
        for (int j = 0; j < m_AnimationEffects[i]->nameAnimation.size(); j++) {
            if (m_AnimationEffects[i]->nameAnimation[j].second == 0) {
                m_AnimationEffects[i]->nameAnimation[j].second = 1;
                m_AnimationEffects[i]->object->SetRenderer(m_AnimationEffects[i]->nameAnimation[j].first);
                break;
            }
            /*else {
                m_AnimationEffects[i]->nameAnimation[j].second = 0;
            }*/
        }
    }
}

void EffectManager::DestroyAllEffect() {
    for (int i = 0; i < m_AnimationEffects.size(); i++) {
        //if (m_AnimationEffects[i]->object) {
        //    //delete m_AnimationEffects[i]->object;
        //}
        delete m_AnimationEffects[i];
    }
    for (int i = 0; i < m_MoveEffects.size(); i++) {
        //if (m_MoveEffects[i]->object != nullptr) delete m_MoveEffects[i]->object;
        delete m_MoveEffects[i];
    }
    for (int i = 0; i < m_FadedEffects.size(); i++) {
        //if (m_FadedEffects[i]->object != NULL) delete m_FadedEffects[i]->object;
        delete m_FadedEffects[i];
    }
}

EffectManager::~EffectManager() {
    DestroyAllEffect();
}