#pragma once
#include "../Utilities/utilities.h"

class ShaderText
{
private:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint coordAttribute;
	GLint colorUniform;
	GLint textUniform;

public:
	ShaderText();
	int Init();
	GLuint GetProgram();
	GLint GetCoordAttribute();
	GLint GetColorUniform();
	GLint GetTextUniform();
	~ShaderText();
};