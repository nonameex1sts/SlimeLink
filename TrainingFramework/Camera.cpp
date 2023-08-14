#include "stdafx.h"
#include "Camera.h"
#include "Math.h"

Camera::Camera(Vector3 pos, Vector3 target, float fovY, float nearPlane, float farPlane, float speed)
{
	this->pos = pos;
	this->target = target;
	perspective.SetPerspective(fovY, Globals::screenWidth / Globals::screenHeight, nearPlane, farPlane);
	moveSpeed = speed;
	rotateSpeed = speed;
}

Matrix Camera::CalculateViewMatrix()
{
	Vector3 zaxis = (pos - target).Normalize();
	Vector3 xaxis = (up.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();

	Matrix view;
	view.m[0][0] = xaxis.x;				view.m[0][1] = yaxis.x;				view.m[0][2] = zaxis.x;				view.m[0][3] = 0;
	view.m[1][0] = xaxis.y;				view.m[1][1] = yaxis.y;				view.m[1][2] = zaxis.y;				view.m[1][3] = 0;
	view.m[2][0] = xaxis.z;				view.m[2][1] = yaxis.z;				view.m[2][2] = zaxis.z;				view.m[2][3] = 0;
	view.m[3][0] = -pos.Dot(xaxis);		view.m[3][1] = -pos.Dot(yaxis);		view.m[3][2] = -pos.Dot(zaxis);		view.m[3][3] = 1;

	return view;
}	

Matrix Camera::CalculateWorldMatrix()
{
	Vector3 zaxis = (pos - target).Normalize();
	Vector3 xaxis = (up.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();

	Matrix rotation;
	rotation.m[0][0] = xaxis.x;	rotation.m[0][1] = xaxis.y;	rotation.m[0][2] = xaxis.z;	rotation.m[0][3] = 0;
	rotation.m[1][0] = yaxis.x;	rotation.m[1][1] = yaxis.y;	rotation.m[1][2] = yaxis.z;	rotation.m[1][3] = 0;
	rotation.m[2][0] = zaxis.x;	rotation.m[2][1] = zaxis.y;	rotation.m[2][2] = zaxis.z;	rotation.m[2][3] = 0;
	rotation.m[3][0] = 0;		rotation.m[3][1] = 0;		rotation.m[3][2] = 0;		rotation.m[3][3] = 1;

	Matrix transalate;
	transalate.m[0][0] = 1;			transalate.m[0][1] = 0;			transalate.m[0][2] = 0;			transalate.m[0][3] = 0;
	transalate.m[1][0] = 0;			transalate.m[1][1] = 1;			transalate.m[1][2] = 0;			transalate.m[1][3] = 0;
	transalate.m[2][0] = 0;			transalate.m[2][1] = 0;			transalate.m[2][2] = 1;			transalate.m[2][3] = 0;
	transalate.m[3][0] = -pos.x;	transalate.m[3][1] = -pos.y;	transalate.m[3][2] = -pos.z;	transalate.m[3][3] = 1;

	return rotation * transalate;
}

Matrix Camera::GetPerspectiveMatrix()
{
	return perspective;
}

void Camera::Inputs(float deltaTime, unsigned char keyPressed)
{
	Vector3 deltaMove = -(pos - target).Normalize() * deltaTime * moveSpeed;
	Vector4 localTarget = Vector4(0, 0, -(pos - target).Length(), 0.0f);
	Vector4 localNewTarget, worldNewTarget;
	Matrix rotationTemp;	//For storing rotation matrix

	Vector3 zaxis = (pos - target).Normalize();
	Vector3 xaxis = (up.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();

	// 0 1 2 3 for arrowkey movement
	if (keyPressed & (1 << 0)) {
		pos -= deltaMove.Cross(up);
		target -= deltaMove.Cross(up);
	}
	if (keyPressed & (1 << 1)) {
		pos += deltaMove;
		target += deltaMove;
	}
	if (keyPressed & (1 << 2)) {
		pos += deltaMove.Cross(up);
		target += deltaMove.Cross(up);
	}
	if (keyPressed & (1 << 3)) {
		pos -= deltaMove;
		target -= deltaMove;
	}

	// 4 5 6 7 for a w d s rotation
	if (keyPressed & (1 << 4)) {
		localNewTarget = localTarget * rotationTemp.SetRotationAngleAxis(deltaTime * rotateSpeed, yaxis.x, yaxis.y, yaxis.z);
		worldNewTarget = localNewTarget * CalculateWorldMatrix();
		target.x = worldNewTarget.x;
		target.y = worldNewTarget.y;
		target.z = worldNewTarget.z;
	}
	if (keyPressed & (1 << 5)) {
		localNewTarget = localTarget * rotationTemp.SetRotationAngleAxis(deltaTime * -rotateSpeed, xaxis.x, xaxis.y, xaxis.z);
		worldNewTarget = localNewTarget * CalculateWorldMatrix();
		target.x = worldNewTarget.x;
		target.y = worldNewTarget.y;
		target.z = worldNewTarget.z;
	}
	if (keyPressed & (1 << 6)) {
		localNewTarget = localTarget * rotationTemp.SetRotationAngleAxis(deltaTime * -rotateSpeed, yaxis.x, yaxis.y, yaxis.z);
		worldNewTarget = localNewTarget * CalculateWorldMatrix();
		target.x = worldNewTarget.x;
		target.y = worldNewTarget.y;
		target.z = worldNewTarget.z;
	}
	if (keyPressed & (1 << 7)) {
		localNewTarget = localTarget * rotationTemp.SetRotationAngleAxis(deltaTime * rotateSpeed, xaxis.x, xaxis.y, xaxis.z);
		worldNewTarget = localNewTarget * CalculateWorldMatrix();
		target.x = worldNewTarget.x;
		target.y = worldNewTarget.y;
		target.z = worldNewTarget.z;
	}
}

void Camera::MoveLeft(float deltaTime) {
	Vector3 deltaMove = -(pos - target).Normalize() * deltaTime * moveSpeed;
	pos -= deltaMove.Cross(up);
	target -= deltaMove.Cross(up);
}

void Camera::MoveRight(float deltaTime) {
	Vector3 deltaMove = -(pos - target).Normalize() * deltaTime * moveSpeed;
	pos += deltaMove.Cross(up);
	target += deltaMove.Cross(up);
}

void Camera::MoveForward(float deltaTime) {
	Vector3 deltaMove = -(pos - target).Normalize() * deltaTime * moveSpeed;
	pos += deltaMove;
	target += deltaMove;
}

void Camera::MoveBackward(float deltaTime) {
	Vector3 deltaMove = -(pos - target).Normalize() * deltaTime * moveSpeed;
	pos -= deltaMove;
	target -= deltaMove;
}

void Camera::RotateLeft(float deltaTime) {
	Vector4 localTarget = Vector4(0, 0, -(pos - target).Length(), 0.0f);
	Vector4 localNewTarget, worldNewTarget;
	Matrix rotationTemp;	//For storing rotation matrix

	Vector3 zaxis = (pos - target).Normalize();
	Vector3 xaxis = (up.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();

	localNewTarget = localTarget * rotationTemp.SetRotationAngleAxis(deltaTime * rotateSpeed, yaxis.x, yaxis.y, yaxis.z);
	worldNewTarget = localNewTarget * CalculateWorldMatrix();
	target.x = worldNewTarget.x;
	target.y = worldNewTarget.y;
	target.z = worldNewTarget.z;
}

void Camera::RotateRight(float deltaTime) {
	Vector4 localTarget = Vector4(0, 0, -(pos - target).Length(), 0.0f);
	Vector4 localNewTarget, worldNewTarget;
	Matrix rotationTemp;	//For storing rotation matrix

	Vector3 zaxis = (pos - target).Normalize();
	Vector3 xaxis = (up.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();

	localNewTarget = localTarget * rotationTemp.SetRotationAngleAxis(deltaTime * -rotateSpeed, yaxis.x, yaxis.y, yaxis.z);
	worldNewTarget = localNewTarget * CalculateWorldMatrix();
	target.x = worldNewTarget.x;
	target.y = worldNewTarget.y;
	target.z = worldNewTarget.z;
}

void Camera::RotateUp(float deltaTime) {
	Vector4 localTarget = Vector4(0, 0, -(pos - target).Length(), 0.0f);
	Vector4 localNewTarget, worldNewTarget;
	Matrix rotationTemp;	//For storing rotation matrix

	Vector3 zaxis = (pos - target).Normalize();
	Vector3 xaxis = (up.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();

	localNewTarget = localTarget * rotationTemp.SetRotationAngleAxis(deltaTime * -rotateSpeed, xaxis.x, xaxis.y, xaxis.z);
	worldNewTarget = localNewTarget * CalculateWorldMatrix();
	target.x = worldNewTarget.x;
	target.y = worldNewTarget.y;
	target.z = worldNewTarget.z;
}

void Camera::RotateDown(float deltaTime) {
	Vector4 localTarget = Vector4(0, 0, -(pos - target).Length(), 0.0f);
	Vector4 localNewTarget, worldNewTarget;
	Matrix rotationTemp;	//For storing rotation matrix

	Vector3 zaxis = (pos - target).Normalize();
	Vector3 xaxis = (up.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();

	localNewTarget = localTarget * rotationTemp.SetRotationAngleAxis(deltaTime * rotateSpeed, xaxis.x, xaxis.y, xaxis.z);
	worldNewTarget = localNewTarget * CalculateWorldMatrix();
	target.x = worldNewTarget.x;
	target.y = worldNewTarget.y;
	target.z = worldNewTarget.z;
}

Camera::~Camera()
{
}
