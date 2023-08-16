#include "stdafx.h"
#include "Object.h"

Object::Object(Model* pModel, Texture* pTexture, Camera* pCamera, Shaders* pShader, Vector3 position, Vector3 rotation, Vector3 scale)
{
	this->pModel = pModel;
	this->pTexture = pTexture;
	this->pCamera = pCamera;
	this->pShader = pShader;
	InitWorldMatrix(position, rotation, scale);
}

Object::Object(char* pModelLink, char* pTextureLink, Camera* camera, Vector3 position, Vector3 rotation, Vector3 scale) 
{
	//Initialize pModel
	pModel = new Model(pModelLink);
	//pModel->BindBuffer();

	//Initialize pTexture
	pTexture = new Texture(pTextureLink);

	//Initialize shader
	pShader = new Shaders();

	//Initialize world matrix
	InitWorldMatrix(position, rotation, scale);

	//Initialize camera
	this->pCamera = pCamera;
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

	mt_world = Scale * Rotation * Translation;
}

void Object::Update()
{
}

void Object::Draw() 
{
	//Bind pModel, texture and shader buffer
	glBindBuffer(GL_ARRAY_BUFFER, pModel->GetVBOId());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pModel->GetIBOId());
	glBindTexture(GL_TEXTURE_2D, pTexture->GetTextureId());
	
	glUseProgram(pShader->GetProgram());

	// Get position attribute
	if (pShader->GetPositionAttribute() != -1)
	{
		glEnableVertexAttribArray(pShader->GetPositionAttribute());
		glVertexAttribPointer(pShader->GetPositionAttribute(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	// Get uv position for texture
	if (pShader->GetUVPosition() != -1)
	{
		glEnableVertexAttribArray(pShader->GetUVPosition());
		glVertexAttribPointer(pShader->GetUVPosition(), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3)));
	}

	// Get texture
	if (pShader->GetTextureUniform() != -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(pShader->GetTextureUniform(), 0);
	}

	glUniform1i(pShader->GetTextureUniform(), 0);

	//Calculate world_view_perspective matrix
	glUniformMatrix4fv(pShader->GetWVPUniform(), 1, false, &CalculateWVP().m[0][0]);

	// Draw object
	glDrawElements(GL_TRIANGLES, pModel->GetNumberOfIndicies(), GL_UNSIGNED_INT, 0);

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
	return mt_world * pCamera->CalculateViewMatrix() * pCamera->GetOrthogonalMatrix();
}

Object::~Object() {}
