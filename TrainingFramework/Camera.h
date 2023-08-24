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
	Matrix orthogonal;
	float moveSpeed;
	float rotateSpeed;

	bool isMoving = false;
	Vector3 deltaPosition;
	Vector3 nextPosition;

public:
	Camera(Vector3 pos, Vector3 target, float fovY, float aspect, float nearPlane, float farPlane);
	Matrix CalculateViewMatrix();
	Matrix CalculateWorldMatrix();
	Matrix GetOrthogonalMatrix();
	Matrix GetPerspectiveMatrix();
	void Inputs(unsigned char keyPressed);
	void Move(float deltaTime);
	~Camera();
};