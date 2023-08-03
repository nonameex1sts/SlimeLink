#pragma once
#include "Math.h"
#include "Vertex.h"
#include "../Utilities/utilities.h"

class Model {
public:
	GLuint inumVertex;
	GLuint inumIndices;
	Vertex* vertices;
	GLuint* ivereticalIndices;
	Model(char* filePath);
	~Model();
};