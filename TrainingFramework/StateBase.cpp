#include "stdafx.h"
#include "StateBase.h"

StateBase::StateBase()
{
    m_Name = "Untitled State";
}

string StateBase::GetName()
{
    return m_Name;
}

void StateBase::OnStart()
{
}

void StateBase::Draw()
{
}

void StateBase::Update(float)
{
}

void StateBase::OnTranslation()
{
}

StateBase::~StateBase()
{
}
