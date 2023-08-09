#pragma once
#include "Math.h"
#include "Vertex.h"
#include "../Utilities/utilities.h"

class Model {
private:
	GLuint inumIndices;
	GLuint vboId;
	GLuint iboId;

public:
	Model();
	Model(char* filePath);
	GLuint GetNumberOfIndicies();
	GLuint GetVBOId();
	GLuint GetIBOId();
	void Cleanup();
	~Model();
};