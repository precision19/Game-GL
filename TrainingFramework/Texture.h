#pragma once
#include "../Utilities/utilities.h"
#include <string>

using namespace std;

class Texture
{
protected:
	GLuint textureId;
public:
	Texture() { textureId = -1; };
	Texture(const char*);
	Texture(const char*, string, string, string);
	virtual void BindBuffer(int, bool = true);
	~Texture();
};

