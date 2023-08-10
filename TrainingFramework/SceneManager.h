#pragma once
#include "Camera.h"
#include "Object.h"
#include "ResourceManager.h"
#include "../Utilities/utilities.h"
#include "Math.h"

class SceneManager {
private:
	Camera* camera;
	Object** objects;
	int numObjects;

public:
	SceneManager(ResourceManager* resourceManager);
	void Update(ESContext* esContext, float deltaTime, unsigned char keyPressed);
	void Draw();
	~SceneManager();
};
