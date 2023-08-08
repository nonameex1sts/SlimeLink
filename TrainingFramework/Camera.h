#pragma once
#include "../Utilities/utilities.h"
#include "Math.h"
#include "Globals.h"

class Camera {
public:
	Vector3 pos;
	Vector3 target;
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

	float speed = 1.0f;

	Camera(Vector3 pos, Vector3 target);
	Matrix CalculateViewMatrix();
	Matrix CalculateWorldMatrix();
	Matrix CalculatePerspectiveMatrix();
	void Inputs(float deltaTime, unsigned char keyPressed);
	~Camera();
};