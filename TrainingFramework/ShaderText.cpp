#include "stdafx.h"
#include "ShaderText.h"

ShaderText::ShaderText()
{
}

int ShaderText::Init()
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, "../Resources/Shaders/TextShaderVS.vs");

	if (vertexShader == 0)
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, "../Resources/Shaders/TextShaderFS.fs");

	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	coordAttribute = glGetAttribLocation(program, "coord");

	textUniform = glGetUniformLocation(program, "tex");

	colorUniform = glGetUniformLocation(program, "color");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 0;
}

GLuint ShaderText::GetProgram()
{
	return program;
}

GLint ShaderText::GetCoordAttribute()
{
	return coordAttribute;
}

GLint ShaderText::GetColorUniform()
{
	return colorUniform;
}

GLint ShaderText::GetTextUniform()
{
	return textUniform;
}

ShaderText::~ShaderText()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
