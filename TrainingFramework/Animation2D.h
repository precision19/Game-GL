#pragma once
#include "Renderer2D.h"

class Animation2D :
    public Renderer2D
{
protected:
	vector<Texture*> m_Sprites;
	int m_CurrentSpriteId;
	float m_FramePerSec;
	float m_animationCurrent;
	bool m_Loop;
public:
	Animation2D();
	Animation2D(string);
	Renderer* Clone();
	void SetTexture(int);
	void SetTexture(string);
	void SetFPS(int);
	void SetLoop(bool);
	void Update(float);
	~Animation2D();
};

