#include "stdafx.h"
#include "Object.h"

Object::Object(Model* model, Texture* texture, Camera* camera, Shaders* shader, Vector3 position, Vector3 rotation, Vector3 scale)
{
	this->model = model;
	this->texture = texture;
	this->camera = camera;
	this->shader = shader;
	InitWorldMatrix(position, rotation, scale);
}

Object::Object(char* modelLink, char* textureLink, Camera* camera, Vector3 position, Vector3 rotation, Vector3 scale) {
	//Initialize model
	model = new Model(modelLink);
	//model->BindBuffer();

	//Initialize texture
	texture = new Texture(textureLink);

	//Initialize shader
	shader = new Shaders();

	//Initialize world matrix
	InitWorldMatrix(position, rotation, scale);

	//Initialize camera
	this->camera = camera;
}

void Object::InitWorldMatrix(Vector3 position, Vector3 rotation, Vector3 scale)
{
	Matrix Scale, Rotation, RotationX, RotationY, RotationZ, Translation;
	Scale.SetScale(scale.x, scale.y, scale.z);

	RotationX.SetRotationX(rotation.x);
	RotationY.SetRotationY(rotation.y);
	RotationZ.SetRotationZ(rotation.z);
	Rotation = RotationZ * RotationX * RotationY;

	Translation.SetTranslation(position.x, position.y, position.z);

	world = Scale * Rotation * Translation;
}

void Object::Update()
{
}

void Object::Draw() {
	//Bind model, texture and shader buffer
	glBindBuffer(GL_ARRAY_BUFFER, model->GetVBOId());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->GetIBOId());
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureId());
	
	glUseProgram(shader->GetProgram());

	// Get position attribute
	if (shader->GetPositionAttribute() != -1)
	{
		glEnableVertexAttribArray(shader->GetPositionAttribute());
		glVertexAttribPointer(shader->GetPositionAttribute(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	// Get uv position for texture
	if (shader->GetUVPosition() != -1) {
		glEnableVertexAttribArray(shader->GetUVPosition());
		glVertexAttribPointer(shader->GetUVPosition(), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3)));
	}

	// Get texture
	if (shader->GetTextureUniform() != -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(shader->GetTextureUniform(), 0);
	}

	glUniform1i(shader->GetTextureUniform(), 0);

	//Calculate world_view_perspective matrix
	glUniformMatrix4fv(shader->GetWVPUniform(), 1, false, &CalculateWVP().m[0][0]);

	// Draw object
	glDrawElements(GL_TRIANGLES, model->GetNumberOfIndicies(), GL_UNSIGNED_INT, 0);

	//Close buffer
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Object::Key()
{
}

void Object::Move()
{
}

void Object::Rotate()
{
}

Matrix Object::CalculateWVP()
{
	return world * camera->CalculateViewMatrix() * camera->GetPerspectiveMatrix();
}

Object::~Object() {}
