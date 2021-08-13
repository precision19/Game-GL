#pragma once
#include "GameObject.h"
class Block :
    public GameObject
{
public:
    Block();
    Object* Clone();
    void CreateCollider();
};

