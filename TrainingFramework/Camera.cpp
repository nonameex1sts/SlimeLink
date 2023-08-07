#include "stdafx.h"
#include "Camera.h"
#include "Math.h"

Camera::Camera(int width, int height, Vector3 pos, Vector3 target)
{
	this->width = width;
	this->height = height;
	this->pos = pos;
	this->target = target;
}

Matrix Camera::CalculateViewMatrix()
{
	Vector3 zaxis = (pos - target).Normalize();
	Vector3 xaxis = (up.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();

	Matrix rotation = Matrix(0.0f);
	rotation.m[0][0] = xaxis.x;	rotation.m[0][1] = xaxis.y;	rotation.m[0][2] = xaxis.z;	rotation.m[0][3] = 0;
	rotation.m[1][0] = yaxis.x;	rotation.m[1][1] = yaxis.y;	rotation.m[1][2] = yaxis.z;	rotation.m[1][3] = 0;
	rotation.m[2][0] = zaxis.x;	rotation.m[2][1] = zaxis.y;	rotation.m[2][2] = zaxis.z;	rotation.m[2][3] = 0;
	rotation.m[3][0] = 0;		rotation.m[3][1] = 0;		rotation.m[3][2] = 0;		rotation.m[3][3] = 1;

	Matrix transalate = Matrix(0.0f);
	transalate.m[0][0] = 1;			transalate.m[0][1] = 0;			transalate.m[0][2] = 0;			transalate.m[0][3] = 0;
	transalate.m[1][0] = 0;			transalate.m[1][1] = 1;			transalate.m[1][2] = 0;			transalate.m[1][3] = 0;
	transalate.m[2][0] = 0;			transalate.m[2][1] = 0;			transalate.m[2][2] = 1;			transalate.m[2][3] = 0;
	transalate.m[3][0] = -pos.x;	transalate.m[3][1] = -pos.y;	transalate.m[3][2] = -pos.z;	transalate.m[3][3] = 1;

	Matrix view = (rotation * transalate).Transpose();
	return view;
}	

Matrix Camera::CalculateWorldMatrix()
{
	return CalculateViewMatrix().Transpose();
}

Matrix Camera::CalculatePerspectiveMatrix()
{
	Matrix perspective;
	return perspective.SetPerspective(1.0f, 1.0f, 0.1f, 500.0f);
}

void Camera::Inputs(float deltaTime, int keyPressed)
{
	Vector3 deltaMove = -(pos - target).Normalize() * deltaTime *speed;
	Vector4 localTarget = Vector4(0, 0, -(pos - target).Length(), 1.0f);
	Vector4 localNewTarget, worldNewTarget;
	Matrix rotationTemp;

	// 0 1 2 3 for arrowkey movement, 4 5 6 7 for a w d s rotation
	switch (keyPressed)
	{
	case 1<<0:
		pos += deltaMove.Cross(up);
		target += deltaMove.Cross(up);
		break;
	case 1<<1:
		pos += deltaMove;
		target += deltaMove;
		break;
	case 1<<2:
		pos -= deltaMove.Cross(up);
		target -= deltaMove.Cross(up);
		break;
	case 1<<3:
		pos -= deltaMove;
		target -= deltaMove;
		break;
	case 1<<4:
		localNewTarget = localTarget * rotationTemp.SetRotationY(deltaTime * speed);
		worldNewTarget = localNewTarget * CalculateWorldMatrix();
		target.x = worldNewTarget.x;
		target.y = worldNewTarget.y;
		target.z = worldNewTarget.z;
		break;
	case 1<<5:
		localNewTarget = localTarget * rotationTemp.SetRotationX(deltaTime * speed);
		worldNewTarget = localNewTarget * CalculateWorldMatrix();
		target.x = worldNewTarget.x;
		target.y = worldNewTarget.y;
		target.z = worldNewTarget.z;
		break;
	case 1<<6:
		localNewTarget = localTarget * rotationTemp.SetRotationY(deltaTime * -speed);
		worldNewTarget = localNewTarget * CalculateWorldMatrix();
		target.x = worldNewTarget.x;
		target.y = worldNewTarget.y;
		target.z = worldNewTarget.z;
		break;
	case 1<<7:
		localNewTarget = localTarget * rotationTemp.SetRotationX(deltaTime * -speed);
		worldNewTarget = localNewTarget * CalculateWorldMatrix();
		target.x = worldNewTarget.x;
		target.y = worldNewTarget.y;
		target.z = worldNewTarget.z;
		break;
	default:
		break;
	}
	
}

Camera::~Camera()
{
}
