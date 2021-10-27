#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Application.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = false);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	SDL_Texture* graphics;
	PhysBody* player;

	int playerX;
	int playerY;

public:

};