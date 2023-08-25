#include "stdafx.h"
#include "Camera.h"
#include "Math.h"

Camera::Camera(Vector3 pos, Vector3 target, float fovY, float nearPlane, float farPlane, float speed)
{
	this->pos = pos;
	this->target = target;
	perspective.SetPerspective(fovY, Globals::screenWidth / Globals::screenHeight, nearPlane, farPlane);
	orthogonal.SetOrthogonal(0.0f, Globals::screenHeight, 0.0f, Globals::screenWidth, nearPlane, farPlane);
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

Matrix Camera::GetOrthogonalMatrix()
{
	return orthogonal;
}

Matrix Camera::GetPerspectiveMatrix()
{
	return perspective;
}

void Camera::Inputs(unsigned char keyPressed)
{
	//If key is pressed, active the camera moving ability, calculate next position and the direction to move (deltaPosition)
	if (keyPressed & (1 << 0))
	{
		deltaPosition = Vector3(-SQUARE_SIZE, 0.0f, 0.0f);
		isMoving = true;
		nextPosition = pos + deltaPosition;
	}
	if (keyPressed & (1 << 1))
	{
		deltaPosition = Vector3(0.0f, -SQUARE_SIZE, 0.0f);
		isMoving = true;
		nextPosition = pos + deltaPosition;
	}
	if (keyPressed & (1 << 2))
	{
		deltaPosition = Vector3(SQUARE_SIZE, 0.0f, 0.0f);
		isMoving = true;
		nextPosition = pos + deltaPosition;
	}
	if (keyPressed & (1 << 3))
	{
		deltaPosition = Vector3(0.0f, SQUARE_SIZE, 0.0f);
		isMoving = true;
		nextPosition = pos + deltaPosition;
	}
}

void Camera::Move(float deltaTime) {
	if (isMoving)
	{
		//If camera's position is close to its next postion, the camera (position and target) jump to its next postion and disable is moving ability
		if ((pos - nextPosition).Length() < MOVEMENT_SNAP_DISTANCE)
		{
			pos = nextPosition;
			target = nextPosition - Vector3(0.0f, 0.0f, 1.0f);
			isMoving = false;
		}
		//If not, the camera jump a small step towards its next postion direction in each frame
		else
		{
			pos += deltaPosition * FRAME_TIME / (DELAY_KEY_TIME);
			target += deltaPosition * FRAME_TIME / (DELAY_KEY_TIME);
		}
	}
}

Camera::~Camera()
{
}
