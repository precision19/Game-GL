#include "stdafx.h"
#include "Model.h"
#include <iostream>

Model::Model(string name, bool isTerrain)
{
	m_Name = name;

	string path = "Models/" + name + ".nfg";
	FILE* f = fopen(path.c_str(), "r+");

	if (f == NULL)
	{
		printf("Invalid file %s\n", path.c_str());
		exit(1);
	}

	char header[20];
	int amountOfVertexs;
	fscanf(f, "NrVertices: %d\n", &amountOfVertexs);

	Vertex* vertices = new Vertex[amountOfVertexs];

	for (int i = 0; i < amountOfVertexs; i++)
	{
		float posX, posY, posZ;
		float normX, normY, normZ;
		float binormX, binormY, binormZ;
		float tgtX, tgtY, tgtZ;
		float uvU, uvV;
		fscanf(f, "%s pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\n",
			&header, &posX, &posY, &posZ, &normX, &normY, &normZ, &binormX, &binormY, &binormZ, &tgtX, &tgtY, &tgtZ, &uvU, &uvV);
		vertices[i].pos = Vector3(posX, posY, posZ);
		vertices[i].uv = Vector2(uvU, uvV);
	}

	fscanf(f, "NrIndices: %d\n", &amountOfIndices);

	unsigned int* indices = new unsigned int[amountOfIndices];

	for (int i = 0; i < amountOfIndices / 3; i++)
	{
		int x, y, z;
		fscanf(f, "%s %d, %d, %d\n", &header, &x, &y, &z);
		indices[i * 3] = x;
		indices[i * 3 + 1] = y;
		indices[i * 3 + 2] = z;
	}

	if (isTerrain)
	{
		string heightMapPath = "Textures/" + name + ".tga";
		SetHeightmap(vertices, amountOfVertexs, heightMapPath.c_str());
	}

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, amountOfVertexs * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, amountOfIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	fclose(f);
	delete[] vertices;
	delete[] indices;
}

string Model::GetName()
{
	return m_Name;
}

void Model::SetHeightmap(Vertex* vertices, int amountOfVertexs, const char* path)
{
	int iWidth, iHeight, iBpp;
	char* imageData = LoadTGA(path, &iWidth, &iHeight, &iBpp); // iBpp = 24
	unsigned char** data = new unsigned char* [iHeight];
	for (int i = 0; i < iHeight; i++)
	{
		data[i] = new unsigned char[iWidth];
	}

	for (int i = 0; i < iHeight; i++)
	{
		for (int j = 0; j < iWidth; j++)
		{
			data[i][j] = *(imageData + (i * iWidth + j) * 3);
		}
	}
	delete[] imageData;

	for (int i = 0; i < amountOfVertexs; i++)
	{
		float u = vertices[i].uv.x;
		float v = 1 - vertices[i].uv.y;

		int x = (int) (u * (float)(iWidth - 1));
		int y = (int) (v * (float)(iHeight - 1));

		int iH = (int) data[y][x];
		vertices[i].pos.y = (float)iH * 0.05;
	}

	for (int i = 0; i < iHeight; i++)
	{
		delete[] data[i];
	}
	delete[] data;
}

void Model::BindBuffer(bool isStarted)
{
	if (isStarted)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);

	} else 
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

void Model::Draw()
{
	glDrawElements(GL_TRIANGLES, amountOfIndices, GL_UNSIGNED_INT, 0);
}

Model::~Model()
{
	glDeleteBuffers(1, &vboId);
	glDeleteBuffers(1, &iboId);
}
