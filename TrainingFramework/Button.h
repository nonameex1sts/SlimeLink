#pragma once
#include "../Utilities/utilities.h"
#include "Math.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"

class Button {
private:
	Model* pModel;
	Texture* pTexture;
	Camera* pCamera;
	Shaders* pShader;
	Matrix mt_world;

public:
	Button();
	Button(Model* model, Texture* texture, Camera* camera, Shaders* shader, Vector3 position, Vector3 rotation, Vector3 scale);
	void InitWorldMatrix(Vector3 position, Vector3 rotation, Vector3 scale);
	void Update();
	void Draw();
	void Key();
	void MouseClick();
	void MouseMove();
	void Move();
	void Rotate();
	Matrix CalculateWVP();
	~Button();
};