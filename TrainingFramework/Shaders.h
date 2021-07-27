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
	int m_States;
public:
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
	Shaders(char* fileVertexShader, char* fileFragmentShader);
	int Init(char * fileVertexShader, char * fileFragmentShader);
	void SetStates(char*, int);
	void Use(Matrix);
	~Shaders();
};