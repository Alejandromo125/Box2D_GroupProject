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
	PhysBody* holeSensor1;
	PhysBody* holeSensor2;
	PhysBody* holeSensor3;

	PhysBody* diamondSensor1;
	PhysBody* diamondSensor2;
	PhysBody* diamondSensor3;
	PhysBody* diamondSensor4;
	PhysBody* diamondSensor5;
	PhysBody* diamondSensor6;
	PhysBody* diamondSensorBig;

	PhysBody* multiBallSensor;
	PhysBody* eggSensor;
	PhysBody* ringSensor;

	PhysBody* bonusBall1;
	PhysBody* bonusBall2;
	PhysBody* bonusBall3;
	PhysBody* bonusBall4;
	PhysBody* bonusBall5;
	PhysBody* bonusBall6;


	bool sensed;

	SDL_Texture* circle;
	SDL_Texture* circle2;
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
	SDL_Texture* yellowArrows = nullptr;
	SDL_Texture* blueArrows = nullptr;
	SDL_Texture* numberTwo = nullptr;
	SDL_Texture* numberThree = nullptr;
	SDL_Texture* letterG = nullptr;
	SDL_Texture* lettersIN = nullptr;
	SDL_Texture* letterR = nullptr;
	SDL_Texture* timeUp = nullptr;
	SDL_Texture* contrast = nullptr;
	SDL_Texture* multiBall = nullptr;
	SDL_Texture* egg = nullptr;
	SDL_Texture* ring = nullptr;
	SDL_Texture* eggEffect = nullptr;
	SDL_Texture* ringEffect = nullptr;

	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;
	int delay;
	int delay2;
	int delay3;
	SDL_Texture* GameScene = nullptr;
	SDL_Texture* FrontGameScene = nullptr;

	int gameplayTimer;
	int score;

	char timeText[10] = { "\0" };
	int timeFont = -1;

	int bonusBall1PositionX = 0, bonusBall1PositionY = 0;
	int bonusBall2PositionX = 0, bonusBall2PositionY = 0;
	int bonusBall3PositionX = 0, bonusBall3PositionY = 0;
	int bonusBall4PositionX = 0, bonusBall4PositionY = 0;
	int bonusBall5PositionX = 0, bonusBall5PositionY = 0;
	int bonusBall6PositionX = 0, bonusBall6PositionY = 0;

	bool multiBallActive = false;
	int multiBallTimer;

	bool eggActive = false;
	int eggTimer;
	bool ringActive = false;
	int ringTimer;

	int scoreChanger = 1;
};
