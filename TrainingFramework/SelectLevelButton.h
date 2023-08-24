#pragma once
#include "../Utilities/utilities.h"
#include "Button.h"
#include "Math.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"
#include "Object.h"
class SelectLevelButton : public Button
{
private:
	int iCurrentLevel;
public:
	SelectLevelButton();
	SelectLevelButton(Model* pModel, Texture* pTexture, Camera* pCamera, Shaders* pShader, Vector3 position, Vector3 rotation, Vector3 scale, int iType, int isActive);
	~SelectLevelButton();
	void SetCurrentLevel(int iCurrentLevel);
	void MouseClick(int x, int y);
};