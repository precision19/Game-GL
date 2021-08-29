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

EffectManager::EffectManager() 
{

}

void EffectManager::AddMoveEffect(Object* object, Vector3 destination, float timeRemain) {
    MoveEffect* me = new MoveEffect();
    me->object = object;
    me->destination = destination;
    me->timeRemain = timeRemain;
    m_MoveEffects.push_back(me);
}

void EffectManager::AddMoveEffect(Object* object, Vector3 destination, float timeRemain, int eventInvokeId)
{
    MoveEffect* me = new MoveEffect();
    me->object = object;
    me->destination = destination;
    me->timeRemain = timeRemain;
    me->eventInvokeId = eventInvokeId;
    m_MoveEffects.push_back(me);
}

void EffectManager::AddFadedEffect(Object* object, float targetOpacity, float timeRemain) 
{
    FadedEffect* fe = new FadedEffect();
    fe->object = object;
    fe->targetOpacity = targetOpacity;
    fe->timeRemain = timeRemain;
    m_FadedEffects.push_back(fe);
}

void EffectManager::AddFadedEffect(Object* object, float targetOpacity, float timeRemain, int eventInvokeId)
{
    FadedEffect* fe = new FadedEffect();
    fe->object = object;
    fe->targetOpacity = targetOpacity;
    fe->timeRemain = timeRemain;
    fe->eventInvokeId = eventInvokeId;
    m_FadedEffects.push_back(fe);
}

void EffectManager::AddAnimationEffect(Animation2D* animation, Vector3 position)
{
    AnimationEffect* effect = new AnimationEffect();
    effect->animation = (Animation2D *) animation->Clone();
    effect->position = position;
    m_AnimationEffects.push_back(effect);
}

void EffectManager::AddAnimationEffect(Animation2D* animation, Vector3 position, int eventInvokeId)
{
    AnimationEffect* effect = new AnimationEffect();
    effect->animation = (Animation2D*)animation->Clone();
    effect->position = position;
    effect->eventInvokeId = eventInvokeId;
    m_AnimationEffects.push_back(effect);
}


void EffectManager::Update(float deltaTime)
{
    for (int i = 0; i < m_MoveEffects.size(); i++)
    {
        MoveEffect* effect = m_MoveEffects.at(i);
        if (effect->isEnd)
        {
            m_MoveEffects.erase(m_MoveEffects.begin() + i);
            delete effect;
        }
        else
        {
            effect->Update(deltaTime);
        }
    }

    for (int i = 0; i < m_FadedEffects.size(); i++)
    {
        FadedEffect* effect = m_FadedEffects.at(i);
        if (effect->isEnd)
        {
            m_FadedEffects.erase(m_FadedEffects.begin() + i);
            delete effect;
        }
        else
        {
            effect->Update(deltaTime);
        }
    }

    for each (AnimationEffect * effect in m_AnimationEffects)
        effect->Update(deltaTime);
}

void EffectManager::Draw() 
{
    Transform transform;
    for each (AnimationEffect* effect in m_AnimationEffects)
    {
        transform.position = effect->position;
        effect->animation->Draw(transform);
    }
}


void EffectManager::DestroyAllEffect() 
{
    for each (MoveEffect * me in m_MoveEffects)
        delete me;

    for each (FadedEffect * fe in m_FadedEffects)
        delete fe;

    for each (AnimationEffect * ae in m_AnimationEffects)
    {
        delete ae->animation;
        delete ae;
    }
}

EffectManager::~EffectManager() 
{
    DestroyAllEffect();
}