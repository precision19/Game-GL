#pragma once
#include "Renderer.h"
#include <math.h>

class Renderer2D : public Renderer
{
protected:
	vector<Texture*> m_Sprites;
	int m_CurrentSpriteId;
	float anim_cursor;
public:
	Renderer2D();
	void SetTexture(int);
	void SetTexture(string);
	Vector3 GetSize();
	Matrix GetWVP();
	void Update(float);
	~Renderer2D();
};

