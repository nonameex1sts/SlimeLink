#pragma once
#include "Math.h"
#include "Vertex.h"
#include "../Utilities/utilities.h"

class Texture {
public:
	char* imageData;
	int widthImage;
	int heightImage;
	int bppImage;
	GLuint itextureId;
	Texture();
	Texture(char* tgaLink);
	void BindBuffer();
	~Texture();
};