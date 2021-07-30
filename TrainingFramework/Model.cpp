#include "stdafx.h"
#include "Model.h"
#include <iostream>

Model::Model(const char* path)
{
	ifstream ifile;
	ifile.open(path);

	if (ifile.fail())
	{
		printf("Invalid File Name: %s\n", path);
		exit(1);
	}

	string str = "";
	char keyword[20];
	amountOfVertexs;

	getline(ifile, str);
	sscanf(str.c_str(), "%s %d", &keyword, &amountOfVertexs);

	vertices = new Vertex[amountOfVertexs];

	for (int i = 0; i < amountOfVertexs; i++)
	{
		float posX, posY, posZ;
		float normX, normY, normZ;
		float binormX, binormY, binormZ;
		float tgtX, tgtY, tgtZ;
		float uvU, uvV;
		getline(ifile, str);
		sscanf(str.c_str(), "%s pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];",
			&keyword, &posX, &posY, &posZ, &normX, &normY, &normZ, &binormX, &binormY, &binormZ, &tgtX, &tgtY, &tgtZ, &uvU, &uvV);

		// SAVE DATA
		vertices[i].pos.x = posX;
		vertices[i].pos.y = posY;
		vertices[i].pos.z = posZ;

		vertices[i].uv.x = uvU;
		vertices[i].uv.y = uvV;
	}

	getline(ifile, str);
	sscanf(str.c_str(), "%s %d", &keyword, &amountOfIndices);

	indices = new unsigned int[amountOfIndices];

	for (int i = 0; i < amountOfIndices / 3; i++)
	{
		int x, y, z;
		getline(ifile, str);
		sscanf(str.c_str(), "%s %d, %d, %d", &keyword, &x, &y, &z);

		// SAVE DATA
		indices[i * 3] = x;
		indices[i * 3 + 1] = y;
		indices[i * 3 + 2] = z;
	}

	ifile.close();

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, amountOfVertexs * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, amountOfIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Model::Model(const char* path, const char* pathHeightmap)
{
	ifstream ifile;
	ifile.open(path);

	if (ifile.fail())
	{
		printf("Invalid File Name: %s\n", path);
		exit(1);
	}

	string str = "";
	char keyword[20];
	amountOfVertexs;

	getline(ifile, str);
	sscanf(str.c_str(), "%s %d", &keyword, &amountOfVertexs);

	vertices = new Vertex[amountOfVertexs];

	for (int i = 0; i < amountOfVertexs; i++)
	{
		float posX, posY, posZ;
		float normX, normY, normZ;
		float binormX, binormY, binormZ;
		float tgtX, tgtY, tgtZ;
		float uvU, uvV;
		getline(ifile, str);
		sscanf(str.c_str(), "%s pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];",
			&keyword, &posX, &posY, &posZ, &normX, &normY, &normZ, &binormX, &binormY, &binormZ, &tgtX, &tgtY, &tgtZ, &uvU, &uvV);

		// SAVE DATA
		vertices[i].pos.x = posX;
		vertices[i].pos.y = posY;
		vertices[i].pos.z = posZ;

		vertices[i].uv.x = uvU;
		vertices[i].uv.y = uvV;
	}

	getline(ifile, str);
	sscanf(str.c_str(), "%s %d", &keyword, &amountOfIndices);

	indices = new unsigned int[amountOfIndices];

	for (int i = 0; i < amountOfIndices / 3; i++)
	{
		int x, y, z;
		getline(ifile, str);
		sscanf(str.c_str(), "%s %d, %d, %d", &keyword, &x, &y, &z);

		// SAVE DATA
		indices[i * 3] = x;
		indices[i * 3 + 1] = y;
		indices[i * 3 + 2] = z;
	}

	ifile.close();

	SetHeightmap(pathHeightmap);

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, amountOfVertexs * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, amountOfIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Model::SetHeightmap(const char* path)
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
	delete[] vertices;
	delete[] indices;

	glDeleteBuffers(1, &vboId);
	glDeleteBuffers(1, &iboId);
}
