#include <stdafx.h>
#include "Texture.h"
#include <stb/stb_image.h>

Texture::Texture() 
{
}

Texture::Texture(char* tgaLink) 
{
	//Load data
	int widthImage;
	int heightImage;
	int iColorChannel;
	unsigned char* imageData;

	try
	{
		imageData = stbi_load(tgaLink, &widthImage, &heightImage, &iColorChannel, 0);
	}
	catch (...)
	{
		printf("Cannot open image file");
	}

	//Bind buffer
	glGenTextures(1, &itextureId);
	glBindTexture(GL_TEXTURE_2D, itextureId);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	if (iColorChannel == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImage, heightImage, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);	
}

GLuint Texture::GetTextureId()
{
	return itextureId;
}

Texture::~Texture() 
{
}