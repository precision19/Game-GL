#include "stdafx.h"
#include "CubeTexture.h"

CubeTexture::CubeTexture(const char* path)
{
	int iWidth, iHeight, iBpp;
	char* imageData = LoadTGA(path, &iWidth, &iHeight, &iBpp);

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	for (int i = 0; i < 6; i++)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, &imageData[i]);
	}
	delete[] imageData;
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

CubeTexture::CubeTexture(const char* path, string wrap, string filterMin, string filterMag)
{
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

	string link = string(path);
	string paths[6];
	paths[0] = link + "/0.tga";
	paths[1] = link + "/1.tga";
	paths[2] = link + "/2.tga";
	paths[3] = link + "/3.tga";
	paths[4] = link + "/4.tga";
	paths[5] = link + "/5.tga";

	int iWidth, iHeight, iBpp;
	for (unsigned int i = 0; i < 6; i++)
	{
		char* data = LoadTGA(paths[i].c_str(), &iWidth, &iHeight, &iBpp);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		delete[] data;
	}

	if (wrap == "REPEAT")
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else if (wrap == "CLAMP")
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
		printf("WARNING: wrap\n");
	}

	if (filterMin == "LINEAR_LINEAR")
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else if (filterMin == "LINEAR")
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		printf("WARNING: min filter\n");
	}

	if (filterMag == "LINEAR")
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeTexture::BindBuffer(int id, bool isStarted)
{
	switch (id)
	{
	case 0:
		glActiveTexture(GL_TEXTURE0);
		break;
	case 1:
		glActiveTexture(GL_TEXTURE1);
		break;
	case 2:
		glActiveTexture(GL_TEXTURE2);
		break;
	case 3:
		glActiveTexture(GL_TEXTURE3);
		break;
	default:
		break;
	}

	if (isStarted)
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	else 
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
