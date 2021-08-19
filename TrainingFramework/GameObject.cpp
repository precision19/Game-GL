#include "stdafx.h"
#include "GameObject.h"

int GameObject::ms_IDMaker = 0;

GameObject::GameObject(string name)
{
    m_Name = name;
    m_ID = ms_IDMaker;
    ms_IDMaker++;
    m_Collider = NULL;
}

void GameObject::SetCollider(float size)
{
    m_ColliderSize = size;
}

GameObject::GameObject()
{
    m_Name = "Untitled";
    m_ID = ms_IDMaker;
    ms_IDMaker++;
}

Object* GameObject::Clone()
{
    GameObject* copy = new GameObject();
    copy->m_Name = m_Name;
    copy->m_Transform = m_Transform;
    copy->m_Renderer = m_Renderer->Clone();
    copy->m_ColliderSize = m_ColliderSize;
    return copy;
}

void GameObject::Reset()
{

}

void GameObject::CreateCollider()
{
    if (m_Collider == NULL)
    {
        m_Collider = new Box();
    }
    else
    {
        printf("%s already have a collider", m_Name.c_str());
    }
}

int GameObject::GetID()
{
    return m_ID;
}

void GameObject::SetPositionStart(Vector3)
{
}

void GameObject::SetPositionEnd(Vector3)
{
}

void GameObject::OnColliderEnter(GameObject* other)
{
    //printf("Object %d and object %d begin contact\n", m_ID, other->m_ID);
}

void GameObject::OnColliderExit(GameObject* other)
{
    //printf("Object %d and object %d exit contact\n", m_ID, other->m_ID);
}

GameObject::~GameObject() {
    delete m_Collider;
}
