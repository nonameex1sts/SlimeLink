#include <stdafx.h>
#include "Model.h"
#include <cstdio>

Model::Model(char* filePath) {
	FILE* filePointer = fopen(filePath, "r");
	if (filePointer == NULL) {
		// Chua biet
	}
	fscanf(filePointer, "%*s %d", &inumVertex);

	//GLfloat posx, posy, posz, uvx, uvy;
	vertices = new Vertex[inumVertex];
	for (int i = 0; i < inumVertex; i++) {
		fscanf(filePointer, "%*d. pos:[%f, %f, %f]; norm:[%*f, %*f, %*f]; binorm:[%*f, %*f, %*f]; tgt:[%*f, %*f, %*f]; uv:[%f, %f];",
			&vertices[i].pos.x, &vertices[i].pos.y, &vertices[i].pos.z, &vertices[i].uv.x, &vertices[i].uv.y);
		vertices[i].pos.y--;
		//vertices[i].pos = Vector3(posx, posy, posz);
		//vertices[i].uv = Vector2(uvx, uvy);
	}

	fscanf(filePointer, "%*s %d", &inumIndices);

	ivereticalIndices = new GLuint[inumIndices];
	for (int i = 0; i < inumIndices; i+=3) {
		fscanf(filePointer, "%*d. %d, %d, %d;", &ivereticalIndices[i], &ivereticalIndices[i + 1], &ivereticalIndices[i + 2]);
	}

	fclose(filePointer);
};

Model::~Model() {
	delete[] vertices;
	delete[] ivereticalIndices;
};