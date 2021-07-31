#pragma once
#include "../Utilities/utilities.h"
#include <string>
#include <math.h>

using namespace std;

class Texture
{
protected:
	GLuint textureId;
	int iWidth;
	int iHeight;
public:
	Texture();
	Texture(const char*);
	Texture(const char*, string, string, string);
	virtual void BindBuffer(int, bool = true);
	Vector2 GetSize();
	~Texture();
};

