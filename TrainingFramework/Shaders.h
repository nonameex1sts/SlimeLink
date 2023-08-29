#pragma once
#include "../Utilities/utilities.h"

class Shaders
{
private:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute;
	GLint textureUniform;
	GLint wvpUniform;
	GLint uvPosition;

public:
	Shaders();
	int Init(char* fileVertexShader, char* fileFragmentShader);
	GLuint GetProgram();
	GLuint GetPositionAttribute();
	GLuint GetTextureUniform();
	GLuint GetWVPUniform();
	GLuint GetUVPosition();
	GLuint GetUniformLocation(char* name);
	~Shaders();
};