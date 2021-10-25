#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	update_status postUpdate();
	bool CleanUp();

public:
	
	SDL_Texture* introLogo = nullptr;
	SDL_Texture* startButton = nullptr;

	int delay;

};
