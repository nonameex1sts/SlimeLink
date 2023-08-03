// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>


GLuint vboId;
GLuint iboId;
GLuint itextureId;
Shaders myShaders;

int Init(ESContext* esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//triangle data (heap)
	Vertex verticesData[4];

	verticesData[0].pos = Vector3(-0.5f, -0.5f, 0.0f);
	verticesData[1].pos = Vector3(0.5f, -0.5f, 0.0f);
	verticesData[2].pos = Vector3(-0.5f, 0.5f, 0.0f);
	verticesData[3].pos = Vector3(0.5f, 0.5f, 0.0f);

	verticesData[0].uv = Vector2(0.0f, 0.0f);
	verticesData[1].uv = Vector2(1.0f, 0.0f);
	verticesData[2].uv = Vector2(0.0f, 1.0f);
	verticesData[3].uv = Vector2(1.0f, 1.0f);

	GLuint vereticalIndices[] = { 0, 1, 2, 1, 2, 3 };

	//buffer object
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vereticalIndices), vereticalIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//buffer texture
	int widthImage, heightImage, bppImage;

	glGenTextures(GL_TEXTURE_2D, &itextureId);
	glBindTexture(GL_TEXTURE_2D, itextureId);
	char* imageData = LoadTGA("../Resources/Textures/Woman1.tga", &widthImage, &heightImage, &bppImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	//creation of shaders and program 
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

}

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(myShaders.program);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);

	// Get position attribute from shader
	if (myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	  
	// Get uv position for texture
	if (myShaders.uvPosition != -1) {
		glEnableVertexAttribArray(myShaders.uvPosition);
		glVertexAttribPointer(myShaders.uvPosition, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3)));
	}
	
	// Get texture from shader
	if (myShaders.textureUniform != -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(myShaders.textureUniform, 0);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);

	glBindTexture(GL_TEXTURE_2D, itextureId);
	glUniform1i(myShaders.textureUniform, 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, float deltaTime)
{

}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{

}

void CleanUp()
{
	glDeleteBuffers(1, &vboId);
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0)
		return 0;

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}