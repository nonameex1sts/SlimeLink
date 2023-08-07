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

	//Initialize world matrix
	Matrix Scale, Rotation, Translation;
	Scale.SetScale(1.0f, 1.0f, 1.0f);
	Rotation.SetRotationZ(0.0f);
	Translation.SetTranslation(0.0f, 0.0f, 0.0f);

	world = Scale * Rotation * Translation;

	camera = new Camera(Globals::screenWidth, Globals::screenHeight, Vector3(0.0f, 0.0f, -1.5f), Vector3(0.0f, 0.0f, 0.0f));
}

void Object::Draw() {
	//Bind model, texture and shader buffer
	model->BindBuffer();
	texture->BindBuffer();
	
	glUseProgram(shader.program);

	// Get position attribute
	if (shader.positionAttribute != -1)
	{
		glEnableVertexAttribArray(shader.positionAttribute);
		glVertexAttribPointer(shader.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	// Get uv position for texture
	if (shader.uvPosition != -1) {
		glEnableVertexAttribArray(shader.uvPosition);
		glVertexAttribPointer(shader.uvPosition, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3)));
	}

	// Get texture
	if (shader.textureUniform != -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(shader.textureUniform, 0);
	}

	glUniform1i(shader.textureUniform, 0);

	Matrix wvp = world * camera->CalculateViewMatrix() * camera->CalculatePerspectiveMatrix();
	glUniformMatrix4fv(shader.u_WVP, 1, false, &wvp.m[0][0]);

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
	delete camera;
}
