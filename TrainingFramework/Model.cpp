#include <stdafx.h>
#include "Model.h"
#include <cstdio>

Model::Model() {
}

Model::Model(char* filePath) {
	FILE* filePointer = fopen(filePath, "r");
	if (filePointer == NULL) {
		// Unknown
	}

	//Read vertex from file
	fscanf(filePointer, "%*s %d", &inumVertex);

	vertices = new Vertex[inumVertex];
	for (int i = 0; i < inumVertex; i++) {
		fscanf(filePointer, "%*d. pos:[%f, %f, %f]; norm:[%*f, %*f, %*f]; binorm:[%*f, %*f, %*f]; tgt:[%*f, %*f, %*f]; uv:[%f, %f];",
			&vertices[i].pos.x, &vertices[i].pos.y, &vertices[i].pos.z, &vertices[i].uv.x, &vertices[i].uv.y);
		vertices[i].pos.y--;
	}

	//Read indices from file
	fscanf(filePointer, "%*s %d", &inumIndices);

	ivereticalIndices = new GLuint[inumIndices];
	for (int i = 0; i < inumIndices; i+=3) {
		fscanf(filePointer, "%*d. %d, %d, %d;", &ivereticalIndices[i], &ivereticalIndices[i + 1], &ivereticalIndices[i + 2]);
	}

	fclose(filePointer);

	//Bind VBO buffer
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, inumVertex * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//Bind IBO buffer
	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, inumIndices * sizeof(ivereticalIndices[0]), ivereticalIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Model::BindBuffer() {
	glBindBuffer(GL_ARRAY_BUFFER, vboId);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
}

void Model::Cleanup() {
	glDeleteBuffers(1, &vboId);
}

Model::~Model() {
	delete vertices;
	delete ivereticalIndices;
};