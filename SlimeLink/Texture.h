#pragma once
#include "Math.h"
#include "Vertex.h"
#include "../Utilities/utilities.h"

class Texture {
private:
	GLuint itextureId;

public:
	Texture();
	Texture(char* tgaLink);
	GLuint GetTextureId();
	~Texture();
};