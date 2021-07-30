#pragma once

#include "../Utilities/utilities.h"
#include <string>
#include <fstream>
#include "Texture.h"
#include "Vertex.h"

class Sprite 
{
public:

	GLuint vboId2;
	GLuint iboId2;

	int amountVertexs;
	Vertex* vertices;
	int amountIndices;
	unsigned int* indices;

	Sprite(const char*);
	Sprite(const char*, const char*);

	void Init(Vector2 spPosition, Vector2 spSize, Vector2 texSize, Vector2 origin);
	void SetImage(const char* path);
	void BindBuffer(bool = true);
	void Draw();
	~Sprite();
};

