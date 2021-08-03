
#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite(const char* imagePath)
{
	m_Sprite = new Texture(imagePath);
}

Sprite::~Sprite()
{

}
