#pragma once

#include "../Utilities/utilities.h"
#include "Component.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include <string>
#include <vector>

class Sprite : public Component
{
protected:

	Model* m_Model;
	Shaders* m_Shaders;
	vector<Texture*> m_SpriteTexture;
public:
	Sprite(string);
	void Draw(Camera*);
	void Update(float deltaTime);
	~Sprite();
};

