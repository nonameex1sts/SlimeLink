#include "stdafx.h"
#include "Object.h"

Object::Object(){
}

Object::Object(char* modelLink, char* textureLink) {
	//Initialize model
	model = new Model(modelLink);
	//model->BindBuffer();

	//Initialize texture
	texture = new Texture(textureLink);

	//Initialize shader
	shaderInit = shader.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
}

void Object::Draw() {
	//Bind model, texture and shader buffer
	model->BindBuffer();
	texture->BindBuffer();
	shader.BindBuffer();

	// Draw object
	glDrawElements(GL_TRIANGLES, model->inumIndices, GL_UNSIGNED_INT, 0);

	//Close buffer
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Object::Cleanup() {
	model->Cleanup();
}

Object::~Object() {
	delete model;
	delete texture;
}
