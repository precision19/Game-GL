#pragma once
#include "Texture.h"

using namespace std;

class CubeTexture :
	public Texture
{
protected:
	GLuint textureId;
public:
	CubeTexture(const char*);
	CubeTexture(const char*, string, string, string);
	void BindBuffer(int, bool = true);
};

