#pragma once
#include "../Utilities/utilities.h"
#include <string>
#include <math.h>

using namespace std;

class Texture
{
protected:
	string m_Name;

	int iWidth;
	int iHeight;

	GLuint textureId;
public:
	Texture();
	Texture(const char*);
	Texture(string, string, string, string);
	string GetName();
	virtual void BindBuffer(int, bool = true);
	Vector2 GetSize();
	~Texture();
};

