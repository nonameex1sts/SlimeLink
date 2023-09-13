#pragma once
#include "Object.h"
class Animation : public Object
{
private:
	GLint numFrames;
	GLint numActions;
	GLfloat frametime;
	GLint currentFrame;
	GLint currentAction;
	GLfloat currentTime;
	GLint iTempShaderVariableGLID;
public:
	Animation();
	Animation(Model *pModel, Texture* texture, Camera* camera, Shaders* shader, Vector3 position, Vector3 rotation, Vector3 scale, GLint numFrames, GLint numActions, GLint currentAction, GLfloat frametime);
	~Animation();
	void Update(GLfloat deltatime);
	void Draw();
	void SetCurrentAction(GLint currentAction);
	void SetCurrentFrame(GLint currentFrame);
	GLint GetCurrentFrame();
};