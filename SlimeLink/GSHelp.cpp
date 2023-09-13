#include "stdafx.h"
#include "GSHelp.h"
#include "Animation.h"

// Read the animation to showcase in the help state
void GSHelp::ReadAnimation()
{
	FILE* filePointer = fopen("../SlimeLink/HelpPos.txt", "r");

	fscanf(filePointer, "#PICS: %d\n", &iHelpPic);
	startSlime = (int*)malloc(sizeof(int) * iHelpPic);
	endSlime = (int*)malloc(sizeof(int) * iHelpPic);
	startTorch = (int*)malloc(sizeof(int) * iHelpPic);
	endTorch = (int*)malloc(sizeof(int) * iHelpPic);

	// Read slimes pos
	fscanf(filePointer, "#SLIMES: %d\n", &numOfSlime);
	slime = (Animation**)malloc(sizeof(Animation*) * numOfSlime);
	for (int i = 0; i < numOfSlime; i++)
	{
		int id, activated, textureId = 12;
		float posX, posY, posZ;
		slime[i] = (Animation*)malloc(sizeof(Animation));
		fscanf(filePointer, "ID %d\n", &id);
		fscanf(filePointer, "POS %f, %f, %f\n", &posX, &posY, &posZ);
		fscanf(filePointer, "ACTIVE %d\n", &activated);
		if (activated == 0)
		{
			textureId = 14;
		}
		else if (activated == 2)
		{
			textureId = 107;
		}
		*(slime[i]) = Animation(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(textureId), pCamera,
			ResourceManager::GetInstance()->GetShaderById(1), Vector3(posX, posY, posZ), Vector3(0.0f, 0.0f, 0.0f), Vector3(SQUARE_SIZE, SQUARE_SIZE, 0.0f), 6, 1, 0, 0.1);
	}

	// Read torches pos
	fscanf(filePointer, "#TORCHES: %d\n", &numOfTorch);
	torch = (Animation**)malloc(sizeof(Animation*) * numOfTorch);
	for (int i = 0; i < numOfTorch; i++)
	{
		int id;
		float posX, posY, posZ;
		torch[i] = (Animation*)malloc(sizeof(Animation));
		fscanf(filePointer, "ID %d\n", &id);
		fscanf(filePointer, "POS %f, %f, %f\n", &posX, &posY, &posZ);
		*(torch[i]) = Animation(ResourceManager::GetInstance()->GetModelById(0), ResourceManager::GetInstance()->GetTextureById(90), pCamera,
			ResourceManager::GetInstance()->GetShaderById(1), Vector3(posX, posY, posZ), Vector3(0.0f, 0.0f, 0.0f), Vector3(SQUARE_SIZE, SQUARE_SIZE, 0.0f), 4, 1, 0, 0.1);
	}

	// Read each scene need slimes and torches from which start to end index
	for (int i = 0; i < iHelpPic; i++)
	{
		int id;
		fscanf(filePointer, "#SCREEN %d\n", &id);
		fscanf(filePointer, "START SLIME %d\n", &startSlime[i]);
		fscanf(filePointer, "END SLIME %d\n", &endSlime[i]);
		fscanf(filePointer, "START TORCH %d\n", &startTorch[i]);
		fscanf(filePointer, "END TORCH %d\n", &endTorch[i]);
	}

	fclose(filePointer);
}

GSHelp::GSHelp()
{
	Init("../SlimeLink/GSHelp.txt", StateType::STATE_HELP);
	ReadAnimation();
}

GSHelp::~GSHelp()
{
	for (int i = 0; i < numOfSlime; i++)
	{
		free(slime[i]);
	}
	for (int i = 0; i < numOfTorch; i++)
	{
		free(torch[i]);
	}
	free(torch);
	free(slime);
	free(startSlime);
	free(endSlime);
	free(startTorch);
	free(endTorch);
	Exit();
}

void GSHelp::Update(GLfloat deltatime)
{
	for (int i = 0; i < numOfSlime; i++)
	{
		slime[i]->Update(deltatime);
	}
	for (int i = 0; i < numOfTorch; i++)
	{
		torch[i]->Update(deltatime);
	}
}

void GSHelp::MouseClick(int x, int y, bool isPressed)
{
	// NOTE: check all button if it got click or not
	if (isPressed && pButtons != nullptr)
	{
		for (int i = 0; i < inumButtons; i++)
		{
			pButtons[i]->MouseClick(x, y, &iCurrentPic, iHelpPic);

			if (pButtons == nullptr)
			{
				break;
			}
		}
	}
}

void GSHelp::MouseMove(int x, int y)
{
	for (int i = 0; i < inumButtons; i++)
	{
		pButtons[i]->MouseMove(x, y);
	}
}

void GSHelp::Draw()
{
	pPictures[0]->Draw();
	for (int i = 0; i < inumButtons; i++)
	{
		if (pButtons[i]->getActive())
		{
			pButtons[i]->Draw();
		}
	}

	pPictures[iCurrentPic + 1]->Draw();

	for (int i = startSlime[iCurrentPic]; i < endSlime[iCurrentPic]; i++)
	{
		slime[i]->Draw();
	}
	for (int i = startTorch[iCurrentPic]; i < endTorch[iCurrentPic]; i++)
	{
		torch[i]->Draw();
	}
}