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

public:
	Camera(Vector3 pos, Vector3 target, float fovY, float aspect, float nearPlane, float farPlane);
	Matrix CalculateViewMatrix();
	Matrix CalculateWorldMatrix();
	Matrix GetOrthogonalMatrix();
	Matrix GetPerspectiveMatrix();
	void Inputs(float deltaTime, unsigned char keyPressed);
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	void MoveForward(float deltaTime);
	void MoveBackward(float deltaTime);
	void RotateLeft(float deltaTime);
	void RotateRight(float deltaTime);
	void RotateUp(float deltaTime);
	void RotateDown(float deltaTime);
	~Camera();
};