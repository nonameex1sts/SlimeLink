#pragma once
#include "Math.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"
#include "../Utilities/utilities.h"

class Object {
private:
	Model* pModel;
	Texture* pTexture;
	Camera* pCamera;
	Shaders* pShader;
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Matrix mt_world;

public:
	Object();
	Object(Model* model, Texture* texture, Camera* camera, Shaders* shader, Vector3 position, Vector3 rotation, Vector3 scale);
	Object(char* modelLink, char* textureLink, Camera* camera, Vector3 position, Vector3 rotation, Vector3 scale);
	void InitWorldMatrix();
	void Update();
	void Draw();
	void Key(unsigned char keyPressed);
	void Move(Vector3 deltaPosition);
	void Rotate();
	Matrix CalculateWVP();
	~Object();
};