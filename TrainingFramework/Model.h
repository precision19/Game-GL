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

	int amountOfIndices;
public:
	Model(string, bool);
	string GetName();
	void SetHeightmap(Vertex*, int,const char*);
	void BindBuffer(bool = true);
	void Draw();
	~Model();
};

