#include <stdafx.h>
#include "Texture.h"

Texture::Texture() {
}

Texture::Texture(char* tgaLink) {
	//Load data
	int widthImage;
	int heightImage;
	int bppImage;
	char* imageData = LoadTGA(tgaLink, &widthImage, &heightImage, &bppImage);

	//Bind buffer
	glGenTextures(1, &itextureId);
	glBindTexture(GL_TEXTURE_2D, itextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);	

	delete imageData;
}

GLuint Texture::GetTextureId()
{
	return itextureId;
}

Texture::~Texture() {
	
}