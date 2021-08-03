#pragma once

#include "../Utilities/utilities.h"
#include "Component.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "ResourceManager.h"

class Sprite : public Component
{
protected:
	Model* m_Model;
	Shaders* m_Shaders;
	Texture* m_Sprite;
public:
	Sprite(const char*);
	void Draw(Camera*);
	~Sprite();
};

