#pragma once
#include "Math.h"
#include "Vertex.h"
#include "../Utilities/utilities.h"

class Texture {
public:
	GLuint itextureId;
	Texture();
	Texture(char* tgaLink);
	~Texture();
};