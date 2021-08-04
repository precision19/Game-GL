#pragma once
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "Camera.h"
#include <ctime>

#define DEPTH_TEST 1
#define CULL_FACE 1 << 1
#define BLEND 1 << 2

class Shaders 
{
protected:
	string m_Name;
	int m_States;
public:
	string GetName();
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute;
	GLint colorAttribute;
	GLint uvAttribute;

	GLint cameraPositionUniform;
	GLint fogStartUniform;
	GLint fogLengthUniform;

	GLint tilingUniform;
	GLint heightmapUniform;
	GLint textureUniform;
	GLint cubeTextureUniform;
	GLint texture1Uniform;
	GLint texture2Uniform;
	GLint texture3Uniform;
	GLint WVPUniform;
	GLint timeUniform;
	clock_t m_Timer;

	Shaders(string);
	void SetStates(char*, int);
	void UseState();
	void Use(Matrix);
	~Shaders();
};