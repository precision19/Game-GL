#pragma once

#include "../Utilities/utilities.h"
#include <string>
#include <fstream>
#include "Vertex.h"

class Sprite
{
protected:
	GLuint vboId2;
	GLuint iboId2;

	int amountVertexs;
	Vertex* vertices;
	int amountIndices;
	unsigned int* indices;
public:
	Sprite(const char*);
	Sprite(const char*, const char*);

	void Init(Vector2 spPosition, Vector2 spSize, Vector2 texSize, Vector2 origin);
	void SetImage(const char* path);
	void BindBuffer(bool = true);
	void Draw();
	~Sprite();
};

