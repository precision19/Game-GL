#pragma once
#include "../Utilities/utilities.h"
#include <string>
#include <fstream>
#include "Texture.h"
#include "Vertex.h"

using namespace std;

class Model
{
protected:
	string m_Name;

	GLuint vboId;
	GLuint iboId;

	int amountOfVertexs;
	Vertex* vertices;
	int amountOfIndices;
	unsigned int* indices;
public:
	Model(const char* path);
	Model(const char* path, const char* pathHeightmap);
	Model(string, bool);
	string GetName();
	void SetHeightmap(const char* path);
	void BindBuffer(bool = true);
	void Draw();
	~Model();
};

