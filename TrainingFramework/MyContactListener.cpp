#include "stdafx.h"
#include "MyContactListener.h"

MyContactListener::MyContactListener() {

}

MyContactListener::~MyContactListener() {

}

void MyContactListener::BeginContact(b2Contact* contact) {
    Object* obj = (Object*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    if (obj) {
        obj->StartContact();
    }
    obj = (Object*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
    if (obj) {
        obj->StartContact();
    }
}

void MyContactListener::EndContact(b2Contact* contact) {
    Object* obj = (Object*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    if (obj) {
        obj->EndContact();
    }
    obj = (Object*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
    if (obj) {
        obj->EndContact();
    }
}