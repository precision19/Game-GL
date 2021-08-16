#pragma once
#include "Renderer.h"
#include <math.h>

class Renderer2D : public Renderer
{
public:
	Renderer2D();
	Renderer2D(string);
	virtual Renderer* Clone();
	void Draw(Transform);
	virtual ~Renderer2D();
};

