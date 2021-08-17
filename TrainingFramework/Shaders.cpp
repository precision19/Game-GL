#include "stdafx.h"
#include "Shaders.h"

string Shaders::GetName()
{
	return m_Name;
}

Shaders::Shaders(string name)
{
	m_Name = name;
	string pathVS = "Shaders/" + name + ".vs";
	string pathFS = "Shaders/" + name + ".fs";

	vertexShader = esLoadShader(GL_VERTEX_SHADER, (char*)pathVS.c_str());
	if (vertexShader == 0)
	{
		printf("ERROR: %s", (char*)pathVS.c_str());
		return;
	}

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, (char*)pathFS.c_str());

	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		printf("ERROR: %s", (char*)pathFS.c_str());
		return;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_position");
	uvAttribute = glGetAttribLocation(program, "a_uv");
	colorAttribute = glGetAttribLocation(program, "a_color");

	cameraPositionUniform = glGetUniformLocation(program, "u_cameraPosition");
	fogStartUniform = glGetUniformLocation(program, "u_fogStart");
	fogLengthUniform = glGetUniformLocation(program, "u_fogLength");

	opacityUniform = glGetUniformLocation(program, "u_opacity");
	tilingUniform = glGetUniformLocation(program, "u_tiling");
	heightmapUniform = glGetUniformLocation(program, "u_heightmap");
	textureUniform = glGetUniformLocation(program, "u_texture");
	texture1Uniform = glGetUniformLocation(program, "u_texture1");
	texture2Uniform = glGetUniformLocation(program, "u_texture2");
	texture3Uniform = glGetUniformLocation(program, "u_texture3");
	cubeTextureUniform = glGetUniformLocation(program, "u_cube");
	WVPUniform = glGetUniformLocation(program, "u_wvp");
	timeUniform = glGetUniformLocation(program, "u_time");

	m_States = 0;
}

void Shaders::SetStates(char* state, int iBool)
{
	if (strcmp(state, "GL_DEPTH_TEST") == 0)
	{ 
		m_States = iBool ? (m_States | DEPTH_TEST) : m_States;
		return;
	}

	if (strcmp(state, "GL_CULL_FACE") == 0)
	{
		m_States = iBool ? (m_States | CULL_FACE) : m_States;
		return;
	}

	if (strcmp(state, "GL_BLEND") == 0)
	{
		m_States = iBool ? (m_States | BLEND) : m_States;
		return;
	}

	printf("Undefined state\n");
}

void Shaders::UseState()
{
	if (m_States & DEPTH_TEST)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	if (m_States & CULL_FACE)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	if (m_States & BLEND)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);
	}
	else
	{
		glDisable(GL_BLEND);
	}
}

void Shaders::Use(Matrix WVP)
{
	/*if (m_States & DEPTH_TEST)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	if (m_States & CULL_FACE)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	if (m_States & BLEND)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);
	}
	else
	{
		glDisable(GL_BLEND);
	}

	glUseProgram(program);

	if (textureUniform != -1)
	{
		glUniform1i(textureUniform, 0);
		
		if (texture1Uniform != -1)
		{
			glUniform1i(texture1Uniform, 1);

			if (texture2Uniform != -1)
			{
				glUniform1i(texture2Uniform, 2);

				if (texture3Uniform != -1)
				{
					glUniform1i(texture3Uniform, 3);
				}
			}
		}
	}

	if (cameraPositionUniform != -1)
	{
		Vector3 cameraPosition = Camera::GetInstance()->GetPosition();
		glUniform3f(cameraPositionUniform, cameraPosition.x, cameraPosition.y, cameraPosition.z);
		glUniform3f(cameraPositionUniform, 0, 0, 0);
	}

	if (fogStartUniform != -1)
	{
		glUniform1f(fogStartUniform, 10.0);
	}

	if (fogLengthUniform != -1)
	{
		glUniform1f(fogLengthUniform, 10.0);
	}

	if (heightmapUniform != -1)
	{
		glUniform1i(heightmapUniform, 10);
	}

	if (positionAttribute != -1)
	{
		glEnableVertexAttribArray(positionAttribute);
		glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (uvAttribute != -1)
	{
		glEnableVertexAttribArray(uvAttribute);
		glVertexAttribPointer(uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)sizeof(Vector3));
	}

	if (colorAttribute != -1)
	{
		glEnableVertexAttribArray(colorAttribute);
		glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3) + sizeof(Vector2));
	}

	if (tilingUniform != -1)
	{
		glUniform1f(tilingUniform, 20.0);
	}

	if (WVPUniform != -1)
	{
		glUniformMatrix4fv(WVPUniform, 1, GL_FALSE, &WVP.m[0][0]);
	}

	if (timeUniform != -1)
	{
		clock_t t = clock();
		glUniform1f(timeUniform, ((float)t) / CLOCKS_PER_SEC);
	}*/
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}