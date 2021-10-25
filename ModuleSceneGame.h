#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneGame : public Module
{
public:
	ModuleSceneGame(Application* app, bool start_enabled = true);
	~ModuleSceneGame();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:

	p2List<PhysBody*> circles;
	p2List<PhysBody*> bumpersBodys;
	PhysBody* LeftStickBody;
	PhysBody* RightStickBody;
	PhysBody* LeftSliderBody;
	PhysBody* RightSliderBody;
	p2List<PhysBody*> mapLimits;

	PhysBody* sensor;
	bool sensed;

	SDL_Texture* circle;
	SDL_Texture* LeftStick;
	SDL_Texture* RightStick;
	SDL_Texture* RightSlider;
	SDL_Texture* LeftSlider;
	SDL_Texture* bumpers;

	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;

	SDL_Texture* GameScene = nullptr;
};
