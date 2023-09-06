#include "stdafx.h"
#include "Transition.h"
#include "ResourceManager.h"

Transition* Transition::ms_pInstance = nullptr;

/*
	(320, 180) -> (-320, -180)
	(960, 180) -> (1600, -180)
	(960, 540) -> (1600, 900)
	(320, 540) -> (-320, 900)
*/

Transition::Transition() 
{
	status = 0; // It's currently opening right now, so the next one should be closing aka -1
	pCamera = new Camera(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), 1.0f, -1.0f, 1.0f, 10.0f);
	blocks = new Picture(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(2), pCamera,
		ResourceManager::GetInstance()->GetShaderById(0), Vector3(-640.0f, 360.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(1280.0f, 720.0f, 0.0f), 1);
}

Transition::~Transition()
{
	delete blocks;
	delete pCamera;
}

void Transition::Draw()
{
	blocks->Draw();
}

void Transition::Update()
{
	if (status == -1) {
		blocks->Update(Vector3(640.0f, 360.0f, 0.0f), fTransitionTime);
	}
	if (status == 1) {
		blocks->Update(Vector3(-640.0f, 360.0f, 0.0f), fTransitionTime);
	}
}

void Transition::Closing()
{
	SetStatus(-1);
}

void Transition::Opening()
{
	SetStatus(1);
}

void Transition::SetStatus(int status)
{
	this->status = status;
}

int Transition::GetStatus()
{
	return status;
}