#pragma once
#include "Button.h"
#include "PlayerPrefs.h"

class LevelButton :
    public Button
{
protected:
    static Vector3 m_StarPosition[3];

    int m_Star;
    Renderer* m_OnLockRenderer;
    Renderer* m_StarRenderer;
public:
    LevelButton();
    LevelButton(string);
    void SetRenderer(int);
    void SetRenderer(string);
    void SetStar();
    void Draw();
    ~LevelButton();
};

