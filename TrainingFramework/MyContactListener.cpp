#include "stdafx.h"
#include "MyContactListener.h"

MyContactListener::MyContactListener() {

}

MyContactListener::~MyContactListener() {

}

void MyContactListener::BeginContact(b2Contact* contact) {
    Object* obj1 = (Object*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    Object* obj2 = (Object*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
    if (obj1 && obj2) ContactManager::GetInstance()->BenginContact(obj1, obj2);
}

void MyContactListener::EndContact(b2Contact* contact) {
    Object * obj1 = (Object*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    Object* obj2 = (Object*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
    if (obj1 && obj2) {
        ContactManager::GetInstance()->EndContact(obj1, obj2);
    }
}