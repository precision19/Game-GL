#pragma once
#include "Button.h"
class Switch :
    public Button
{
protected:
    Renderer* m_IdleRenderer2;
    Renderer* m_OnPressRenderer2;
    bool m_default;

};

