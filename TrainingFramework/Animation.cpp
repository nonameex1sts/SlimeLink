#include "stdafx.h"
#include "Animation.h"

Animation::Animation() {}

Animation::~Animation() {}

Animation::Animation(Model* pModel, Texture* pTexture, Camera* pCamera, Shaders* pShader, Vector3 position, Vector3 rotation, Vector3 scale, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frametime)
	:Object(pModel, pTexture, pCamera, pShader, position, rotation, scale)
{
	this->numFrames = numFrames;
	this->numActions = numActions;
	this->currentAction = currentAction;
	this->frametime = frametime;
	currentFrame = 0;
	currentTime = 0;
}

void Animation::Update(GLfloat deltatime)
{
	currentTime += deltatime;
	if (currentTime >= frametime)
	{
		currentFrame++;
		if (currentFrame >= numFrames)
		{
			currentFrame = 0;
		}
		currentTime -= frametime;
	}
}

void Animation::Draw()
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

	iTempShaderVariableGLID = -1;
	iTempShaderVariableGLID = pShader->GetUniformLocation((char*)"u_numFrames");
	if (iTempShaderVariableGLID != -1)
	{
		glUniform1f(iTempShaderVariableGLID, numFrames);
	}

	iTempShaderVariableGLID = -1;
	iTempShaderVariableGLID = pShader->GetUniformLocation((char*)"u_currentFrame");
	if (iTempShaderVariableGLID != -1)
	{
		glUniform1f(iTempShaderVariableGLID, currentFrame);
	}

	iTempShaderVariableGLID = -1;
	iTempShaderVariableGLID = pShader->GetUniformLocation((char*)"u_numActions");
	if (iTempShaderVariableGLID != -1)
	{
		glUniform1f(iTempShaderVariableGLID, numActions);
	}

	iTempShaderVariableGLID = -1;
	iTempShaderVariableGLID = pShader->GetUniformLocation((char*)"u_currentAction");
	if (iTempShaderVariableGLID != -1)
	{
		glUniform1f(iTempShaderVariableGLID, currentAction);
	}

	// Draw object
	glDrawElements(GL_TRIANGLES, pModel->GetNumberOfIndicies(), GL_UNSIGNED_INT, 0);

	//Close buffer
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Animation::SetCurrentAction(GLint currentAction)
{
	this->currentAction = currentAction;
}

void Animation::SetCurrentFrame(GLint currentFrame)
{
	this->currentFrame = currentFrame;
}

GLint Animation::GetCurrentFrame()
{
	return currentFrame;
}
