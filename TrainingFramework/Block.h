#pragma once
#include "GameObject.h"

class Block :
    public GameObject
{
public:
    vector<Renderer*> m_BlockRender;
    Vector3 m_Rotate;

    Block();
    void SetRenderer(int);
    void SetRenderer(int, int, int, int);
    void SetListRenderer(int);
    void SetListRenderer(string);
    Object* Clone();
    void DestroyCollider();
    void CreateCollider();
    ~Block();
};
