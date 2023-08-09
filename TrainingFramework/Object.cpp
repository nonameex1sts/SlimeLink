#include "stdafx.h"
#include "Object.h"

Object::Object(char* modelLink, char* textureLink, Camera* camera) {
	//Initialize model
	model = new Model(modelLink);
	//model->BindBuffer();

	//Initialize texture
	texture = new Texture(textureLink);

	//Initialize shader
	shaderInit = shader.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

	//Initialize world matrix
	Matrix Scale, Rotation, RotationX, RotationY, RotationZ, Translation;
	Scale.SetScale(2.0f, 2.0f, 2.0f);

	RotationX.SetRotationX(0.0f);
	RotationY.SetRotationY(3.1416f / 2.0f);
	RotationZ.SetRotationZ(0.0f);
	Rotation = RotationZ * RotationX * RotationY;

	Translation.SetTranslation(-3.0f, -2.0f, 0.0f);

	world = Scale * Rotation * Translation;

	//Initialize camera
	this->camera = camera;
}

void Object::Draw() {
	//Bind model, texture and shader buffer
	glBindBuffer(GL_ARRAY_BUFFER, model->vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->iboId);
	glBindTexture(GL_TEXTURE_2D, texture->itextureId);
	
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

	//Calculate world_view_perspective matrix
	Matrix wvp = world * camera->CalculateViewMatrix() * camera->CalculatePerspectiveMatrix();
	glUniformMatrix4fv(shader.wvpUniform, 1, false, &wvp.m[0][0]);

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
