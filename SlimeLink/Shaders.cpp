#include <stdafx.h>
#include "Shaders.h"
#include "Vertex.h"

Shaders::Shaders()
{
}

int Shaders::Init(char* fileVertexShader, char* fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if (vertexShader == 0)
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");

	/*colorAttribute = glGetAttribLocation(program, "a_color");*/

	textureUniform = glGetUniformLocation(program, "u_texture");

	uvPosition = glGetAttribLocation(program, "a_uv");

	wvpUniform = glGetUniformLocation(program, "u_WVP");

	return 0;
}

GLuint Shaders::GetUniformLocation(char* name)
{
	return glGetUniformLocation(program, name);
}

GLuint Shaders::GetProgram()
{
	return program;
}

GLuint Shaders::GetPositionAttribute()
{
	return positionAttribute;
}

GLuint Shaders::GetTextureUniform()
{
	return textureUniform;
}

GLuint Shaders::GetWVPUniform()
{
	return wvpUniform;
}

GLuint Shaders::GetUVPosition()
{
	return uvPosition;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}