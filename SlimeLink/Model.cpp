#include <stdafx.h>
#include "Model.h"
#include <cstdio>

Model::Model() 
{
}

Model::Model(char* filePath) 
{
	GLuint inumVertex;
	Vertex* p_vertices;
	GLuint* p_ivereticalIndices;

	FILE* filePointer;
	try
	{
		filePointer = fopen(filePath, "r");
	}
	catch (...)
	{
		printf("Cannot open model file");
	}

	//Read vertex from file
	fscanf(filePointer, "%*s %d", &inumVertex);

	p_vertices = new Vertex[inumVertex];
	for (int i = 0; i < inumVertex; i++) 
	{
		fscanf(filePointer, "%*d. pos:[%f, %f, %f]; norm:[%*f, %*f, %*f]; binorm:[%*f, %*f, %*f]; tgt:[%*f, %*f, %*f]; uv:[%f, %f];",
			&p_vertices[i].pos.x, &p_vertices[i].pos.y, &p_vertices[i].pos.z, &p_vertices[i].uv.x, &p_vertices[i].uv.y);
	}

	//Read indices from file
	fscanf(filePointer, "%*s %d", &inumIndices);

	p_ivereticalIndices = new GLuint[inumIndices];
	for (int i = 0; i < inumIndices; i+=3) 
	{
		fscanf(filePointer, "%*d. %d, %d, %d;", &p_ivereticalIndices[i], &p_ivereticalIndices[i + 1], &p_ivereticalIndices[i + 2]);
	}

	fclose(filePointer);

	//Bind VBO buffer
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, inumVertex * sizeof(p_vertices[0]), p_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//Bind IBO buffer
	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, inumIndices * sizeof(p_ivereticalIndices[0]), p_ivereticalIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete p_ivereticalIndices;
	delete p_vertices;
}

GLuint Model::GetNumberOfIndicies()
{
	return inumIndices;
}

GLuint Model::GetVBOId()
{
	return vboId;
}

GLuint Model::GetIBOId()
{
	return iboId;
}

Model::~Model() {
	glDeleteBuffers(1, &vboId);
	glDeleteBuffers(1, &iboId);
};