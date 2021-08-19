#include "stdafx.h"
#include "EventManager.h"

EventManager* EventManager::ms_Instance = NULL;

void EventManager::CreateInstance()
{
    if (ms_Instance == NULL)
        ms_Instance = new EventManager();
}

EventManager* EventManager::GetInstance()
{
    return ms_Instance;
}

void EventManager::DestroyInstance()
{
    if (ms_Instance)
    {
        delete ms_Instance;
        ms_Instance = NULL;
    }
}

EventManager::EventManager()
{
    m_Events.push_back(0);
    m_Events.push_back(0);
    m_Events.push_back(0);
}

void EventManager::InvokeEvent(int eventGroupId, int eventId)
{
    if (eventGroupId < 0 || eventGroupId > m_Events.size())
    {
        printf("WARNING: Event group's ID is out of range");
        return;
    }
    m_Events.at(eventGroupId) = m_Events.at(eventGroupId) | (1 << eventId);
}

bool EventManager::CheckEvent(int eventGroupId, int eventId, bool clearEventFlag)
{
    if (eventGroupId < 0 || eventGroupId > m_Events.size())
    {
        printf("WARNING: Event group's ID is out of range");
        return false;
    }
    bool temp = m_Events.at(eventGroupId) & (1 << eventId);
    if (temp && clearEventFlag)
    {
        m_Events.at(eventGroupId) = m_Events.at(eventGroupId) ^ (1 << eventId);
    }
    return temp;
}