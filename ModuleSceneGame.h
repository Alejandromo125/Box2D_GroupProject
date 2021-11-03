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
	PhysBody* LeftStickAnchor;
	PhysBody* RightStickBody;
	PhysBody* RightStickAnchor;
	PhysBody* LeftSliderBody;
	PhysBody* RightSliderBody;
	p2List<PhysBody*> mapLimits;
	PhysBody* Bouncer;
	PhysBody* BouncerPivot;

	PhysBody* sensorLow;
	bool sensed;

	SDL_Texture* circle;
	SDL_Texture* LeftStick;
	SDL_Texture* RightStick;
	SDL_Texture* RightSlider;
	SDL_Texture* LeftSlider;
	SDL_Texture* bumpers;
	SDL_Texture* flecha1 = nullptr;
	SDL_Texture* flecha2 = nullptr;
	SDL_Texture* flecha3 = nullptr;
	SDL_Texture* flecha4 = nullptr;
	SDL_Texture* flecha5 = nullptr;
	SDL_Texture* flecha6 = nullptr;
	SDL_Texture* flecha7 = nullptr;
	SDL_Texture* flecha8 = nullptr;
	SDL_Texture* flecha9 = nullptr;
	SDL_Texture* twoArrows1 = nullptr;
	SDL_Texture* twoArrows2 = nullptr;
	SDL_Texture* gge1 = nullptr;
	SDL_Texture* gge2 = nullptr;
	SDL_Texture* gge3 = nullptr;
	SDL_Texture* digit1 = nullptr;
	SDL_Texture* digit2 = nullptr;
	SDL_Texture* digit3 = nullptr;

	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;
	int delay;
	int delay2;
	int delay3;
	SDL_Texture* GameScene = nullptr;
	SDL_Texture* FrontGameScene = nullptr;
};
