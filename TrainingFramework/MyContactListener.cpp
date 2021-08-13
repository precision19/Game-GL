#include "stdafx.h"
#include "MyContactListener.h"

MyContactListener* MyContactListener::ms_Instance = NULL;

void MyContactListener::CreateInstance()
{
    if (ms_Instance == NULL)
        ms_Instance = new MyContactListener();
}

void MyContactListener::DestroyInstance()
{
    if (ms_Instance)
    {
        delete ms_Instance;
        ms_Instance = NULL;
    }
}

MyContactListener::MyContactListener()
{

}

MyContactListener::~MyContactListener() 
{

}

void MyContactListener::BeginContact(b2Contact* contact) 
{
    GameObject* obj1 = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    GameObject* obj2 = (GameObject*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;

    if (obj1 && obj2) 
        ContactManager::GetInstance()->BenginContact(obj1, obj2);
}

void MyContactListener::EndContact(b2Contact* contact) 
{
    GameObject* obj1 = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    GameObject* obj2 = (GameObject*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;

    if (obj1 && obj2)
        ContactManager::GetInstance()->EndContact(obj1, obj2);
}