#pragma once
#include "Math.h"
#include "Vertex.h"
#include "../Utilities/utilities.h"

class Model {
public:
	GLuint inumIndices;
	GLuint vboId;
	GLuint iboId;

	Model();
	Model(char* filePath);
	void Cleanup();
	~Model();
};