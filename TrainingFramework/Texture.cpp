#include "stdafx.h"
#include "Texture.h"

Texture::Texture()
{
	textureId = -1;
	iWidth = 0;
	iHeight = 0;
}

Texture::Texture(const char* path)
{
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	int iBpp;
	char* imageData = LoadTGA(path, &iWidth, &iHeight, &iBpp);

	if (imageData == NULL)
	{
		printf("Invalid file %s\n", path);
		exit(1);
	}

	if (iBpp == 24)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	}
	delete[] imageData;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	//glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(string name, string wrap, string filterMin, string filterMag)
{
	m_Name = name;
	string path = "Textures/" + name + ".tga";

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	int iBpp;
	char* imageData = LoadTGA(path.c_str(), &iWidth, &iHeight, &iBpp);

	if (imageData == NULL)
	{
		printf("Invalid file %s\n", path.c_str());
		exit(1);
	}

	if (iBpp == 24)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	}
	delete[] imageData;

	if (wrap == "REPEAT")
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else if (wrap == "CLAMP")
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		printf("WARNING: wrap\n");
	}

	if (filterMin == "LINEAR_LINEAR")
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else if (filterMin == "LINEAR")
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		printf("WARNING: min filter\n");
	}

	if (filterMag == "LINEAR")
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

string Texture::GetName()
{
	return m_Name;
}

void Texture::BindBuffer(int id, bool isStarted)
{
	switch (id)
	{
	case 0:
		glActiveTexture(GL_TEXTURE0);
		break;
	case 1:
		glActiveTexture(GL_TEXTURE0);
		break;
	case 2:
		glActiveTexture(GL_TEXTURE0);
		break;
	case 3:
		glActiveTexture(GL_TEXTURE0);
		break;
	default:
		glActiveTexture(GL_TEXTURE10);
		break;
	}

	if (isStarted)
		glBindTexture(GL_TEXTURE_2D, textureId);
	else
		glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::BindBuffer(bool isStarted)
{
	if (isStarted)
		glBindTexture(GL_TEXTURE_2D, textureId);
	else
		glBindTexture(GL_TEXTURE_2D, 0);
}

Vector3 Texture::GetSize()
{
	return Vector3(iWidth, iHeight, 1);
}

void Texture::Delete()
{

	glDeleteTextures(0, &textureId);
}

Texture::~Texture()
{
//	glDeleteTextures(0, &textureId);
}
