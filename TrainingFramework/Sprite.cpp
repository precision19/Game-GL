
#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite(const char* imagePath)
{
	int iWidth, iHeight, iBpp;
	char* imageData = LoadTGA(imagePath, &iWidth, &iHeight, &iBpp);

	amountVertexs = 4;
	amountIndices = 6;

	vertices = new Vertex[amountVertexs];
	indices = new unsigned int[amountIndices];

	float aspect = iWidth / iHeight;

	//vertices[0].pos = Vector3(-1, 0, 0);
	//vertices[1].pos = Vector3(0, 0, 0);
	//vertices[2].pos = Vector3(-1, 1, 0);
	//vertices[3].pos = Vector3(0, 1, 0);
	vertices[0].pos.x = 0; vertices[0].pos.y = 0; vertices[0].pos.z = 0;
	vertices[1].pos.x = 1; vertices[1].pos.y = 0; vertices[1].pos.z = 0;
	vertices[2].pos.x = 0; vertices[2].pos.y = 1; vertices[2].pos.z = 0;
	vertices[3].pos.x = 1; vertices[3].pos.y = 1; vertices[3].pos.z = 0;

	vertices[0].uv = Vector2(0, 0);
	vertices[1].uv = Vector2(1, 0);
	vertices[2].uv = Vector2(0, 1);
	vertices[3].uv = Vector2(1, 1);


	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 2; indices[4] = 1; indices[5] = 3;

	glGenBuffers(1, &vboId2);
	glBindBuffer(GL_ARRAY_BUFFER, vboId2);
	glBufferData(GL_ARRAY_BUFFER, amountVertexs * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, amountIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] imageData;
}

Sprite::Sprite(const char* path, const char* imagePath)
{
}

void Sprite::Init(Vector2 spPosition, Vector2 spSize, Vector2 texSize, Vector2 origin)
{
}

void Sprite::SetImage(const char* path)
{

}


void Sprite::BindBuffer(bool isStarted)
{
	if (isStarted)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboId2);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId2);

	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void Sprite::Draw()
{
	glDrawElements(GL_TRIANGLES, amountIndices, GL_UNSIGNED_INT, 0);
}

Sprite::~Sprite()
{
	delete[] vertices;
	delete[] indices;

	glDeleteBuffers(1, &vboId2);
	glDeleteBuffers(1, &iboId2);
}
