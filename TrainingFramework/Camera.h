#pragma once
#include "../Utilities/utilities.h"
#include "Math.h"
#include "Globals.h"

class Camera {
private:
	Vector3 pos;
	Vector3 target;
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	Matrix perspective;
	float moveSpeed;
	float rotateSpeed;

public:
	Camera(Vector3 pos, Vector3 target, float fovY, float aspect, float nearPlane, float farPlane);
	Matrix CalculateViewMatrix();
	Matrix CalculateWorldMatrix();
	Matrix GetPerspectiveMatrix();
	void Inputs(float deltaTime, unsigned char keyPressed);
	~Camera();
};