#include <stdafx.h>
#include "Shaders.h"
#include "Vertex.h"

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if ( vertexShader == 0 )
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");

	/*colorAttribute = glGetAttribLocation(program, "a_color");*/

	textureUniform = glGetUniformLocation(program, "u_texture");

	uvPosition = glGetAttribLocation(program, "a_uv");

	return 0;
}

void Shaders::BindBuffer() {
	glUseProgram(program);

	// Get position attribute
	if (positionAttribute != -1)
	{
		glEnableVertexAttribArray(positionAttribute);
		glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	// Get uv position for texture
	if (uvPosition != -1) {
		glEnableVertexAttribArray(uvPosition);
		glVertexAttribPointer(uvPosition, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3)));
	}

	// Get texture
	if (textureUniform != -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(textureUniform, 0);
	}

	glUniform1i(textureUniform, 0);
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}