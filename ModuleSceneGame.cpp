#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneGame.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "p2List.h"
#include "p2Point.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "ModuleFadeToBlack.h"

ModuleSceneGame::ModuleSceneGame(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = NULL;
	flecha1 = NULL;
	flecha2 = NULL;
	flecha3 = NULL;
	flecha4 = NULL;
	flecha5 = NULL;
	flecha6 = NULL;
	flecha7 = NULL;
	flecha8 = NULL;
	flecha9 = NULL;
	twoArrows1 = NULL;
	twoArrows2 = NULL;
	gge1 = NULL;
	gge2 = NULL;
	gge3 = NULL;
	digit1 = NULL;
	digit2 = NULL;
	digit3 = NULL;
	yellowArrows = NULL;
	blueArrows = NULL;
	numberTwo = NULL;
	numberThree = NULL;
	letterG = NULL;
	lettersIN = NULL;
	letterR = NULL;
	blueFourArrows = NULL;
	yellowTwoArrows = NULL;
	ray_on = false;
	sensed = false;
	
}

ModuleSceneGame::~ModuleSceneGame()
{}

// Load assets
bool ModuleSceneGame::Start()
{

	LOG("Loading Game assets");
	bool ret = true;

	b2Filter filter; //it is b in copy

	filter.categoryBits = 1;
	//filter.maskBits = true;
	
	App->renderer->camera.x = App->renderer->camera.y = 0;


	GameScene = App->textures->Load("pinball/sceneGame.png");
	circle = App->textures->Load("pinball/sonic_ball.png");
	circle2 = App->textures->Load("pinball/sonic_ball2.png");
	RightStick = App->textures->Load("pinball/R_Stick.png");
	LeftStick = App->textures->Load("pinball/L_Stick.png");
	bumpers = App->textures->Load("pinball/Obstacle-1.png");
	RightSlider = App->textures->Load("pinball/R_Object2.png");
	LeftSlider = App->textures->Load("pinball/L_Object2.png");
	FrontGameScene = App->textures->Load("pinball/Front_Background.png");

	flecha1 = App->textures->Load("pinball/flecha1.png");
	flecha2 = App->textures->Load("pinball/flecha2.png");
	flecha3 = App->textures->Load("pinball/flecha3.png");
	flecha4 = App->textures->Load("pinball/flecha4.png");
	flecha5 = App->textures->Load("pinball/flecha5.png");
	flecha6 = App->textures->Load("pinball/flecha6.png");
	flecha7 = App->textures->Load("pinball/flecha7.png");
	flecha8 = App->textures->Load("pinball/flecha8.png");
	flecha9 = App->textures->Load("pinball/flecha9.png");
	twoArrows1 = App->textures->Load("pinball/twoArrows1.png");
	twoArrows2 = App->textures->Load("pinball/twoArrows2.png");
	gge1 = App->textures->Load("pinball/gge1.png");
	gge2 = App->textures->Load("pinball/gge2.png");
	gge3 = App->textures->Load("pinball/gge3.png");
	digit1 = App->textures->Load("pinball/digit1.png");
	digit2 = App->textures->Load("pinball/digit2.png");
	digit3 = App->textures->Load("pinball/digit3.png");
	yellowArrows = App->textures->Load("pinball/yellowArrows.png");
	blueArrows = App->textures->Load("pinball/blueArrows.png");
	numberTwo = App->textures->Load("pinball/numberTwo.png");
	numberThree = App->textures->Load("pinball/numberThree.png");
	letterG = App->textures->Load("pinball/letterG.png");
	lettersIN = App->textures->Load("pinball/lettersIN.png");
	letterR = App->textures->Load("pinball/letterR.png");
	timeUp = App->textures->Load("pinball/time_up_L.png");
	contrast = App->textures->Load("pinball/dark_contrast.png");
	multiBall = App->textures->Load("pinball/multiBall.png");
	egg = App->textures->Load("pinball/egg.png");
	ring = App->textures->Load("pinball/ring.png");
	eggEffect = App->textures->Load("pinball/eggEffect.png");
	ringEffect = App->textures->Load("pinball/ringEffect.png");
	sceneUI = App->textures->Load("pinball/sceneGameUI.png");
	blueFourArrows = App->textures->Load("pinball/blueFourArrows.png");
	yellowTwoArrows = App->textures->Load("pinball/yellowTwoArrows.png");
	bouncer = App->textures->Load("pinball/spring.png");

	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	egg_fx = App->audio->LoadFx("pinball/egg.wav");
	multiBall_fx = App->audio->LoadFx("pinball/multiBall.wav");

	if (App->scene_intro->trackID == 1)App->audio->PlayMusic("pinball/capitolio2.ogg", 0.0f);
	if (App->scene_intro->trackID == 2)App->audio->PlayMusic("pinball/sonic_gameplay.ogg", 0.0f);

	char lookupTable[] = { "0123456789" };
	timeFont = App->fonts->Load("pinball/numbers3.png", lookupTable, 1);

	filter.categoryBits = 0x0001;
	filter.maskBits = 0x0001;

	sensorLow = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 10);
	sensorLow->listener = this;
	sensorLow->body->GetFixtureList()->SetFilterData(filter);

	holeSensor1 = App->physics->CreateRectangleSensor(180 + 40 / 2, 245 + 10 / 2, 40, 10);
	holeSensor1->listener = this;
	holeSensor1->body->GetFixtureList()->SetFilterData(filter);

	holeSensor2 = App->physics->CreateRectangleSensor(280 + 40 / 2, 385 + 10 / 2, 40, 10);
	holeSensor2->listener = this;
	holeSensor2->body->GetFixtureList()->SetFilterData(filter);
	
	holeSensor3 = App->physics->CreateRectangleSensor(40 + 40 / 2, 540 + 10 / 2, 40, 10);
	holeSensor3->listener = this;
	holeSensor3->body->GetFixtureList()->SetFilterData(filter);

	diamondSensor1 = App->physics->CreateRectangleSensor(244 + 20 / 2, 790 + 10 / 2, 20, 10);
	diamondSensor1->listener = this;
	diamondSensor1->body->GetFixtureList()->SetFilterData(filter);

	diamondSensor2 = App->physics->CreateRectangleSensor(305 + 20 / 2, 790 + 10 / 2, 20, 10);
	diamondSensor2->listener = this;
	diamondSensor2->body->GetFixtureList()->SetFilterData(filter);

	diamondSensor3 = App->physics->CreateRectangleSensor(365 + 20 / 2, 790 + 10 / 2, 20, 10);
	diamondSensor3->listener = this;
	diamondSensor3->body->GetFixtureList()->SetFilterData(filter);

	diamondSensor4 = App->physics->CreateRectangleSensor(425 + 20 / 2, 790 + 10 / 2, 20, 10);
	diamondSensor4->listener = this;
	diamondSensor4->body->GetFixtureList()->SetFilterData(filter);

	diamondSensor5 = App->physics->CreateRectangleSensor(274 + 20 / 2, 815 + 10 / 2, 20, 10);
	diamondSensor5->listener = this;
	diamondSensor5->body->GetFixtureList()->SetFilterData(filter);

	diamondSensor6 = App->physics->CreateRectangleSensor(396 + 20 / 2, 815 + 10 / 2, 20, 10);
	diamondSensor6->listener = this;
	diamondSensor6->body->GetFixtureList()->SetFilterData(filter);

	diamondSensorBig = App->physics->CreateRectangleSensor(310 + 70 / 2, 830 + 30 / 2, 70, 30);
	diamondSensorBig->listener = this;
	diamondSensorBig->body->GetFixtureList()->SetFilterData(filter);

	multiBallSensor = App->physics->CreateRectangleSensor(640 + 20 / 2, 510 + 130 / 2, 20, 130);
	multiBallSensor->listener = this;
	multiBallSensor->body->GetFixtureList()->SetFilterData(filter);

	eggSensor = App->physics->CreateRectangleSensor(624 + 46 / 2, 335 + 55 / 2, 46, 55);
	eggSensor->listener = this;
	eggSensor->body->GetFixtureList()->SetFilterData(filter);

	ringSensor = App->physics->CreateRectangleSensor(40 + 60 / 2, 315 + 10 / 2, 60, 10);
	ringSensor->listener = this;
	ringSensor->body->GetFixtureList()->SetFilterData(filter);

	int mapPoints1[80] = {
	685, 990,
	740, 990,
	738, 163,
	716, 87,
	660, 41,
	591, 16,
	502, 43,
	327, 27,
	193, 40,
	101, 79,
	49, 133,
	24, 251,
	48, 370,
	91, 463,
	102, 559,
	66, 530,
	29, 543,
	28, 573,
	106, 651,
	61, 666,
	27, 707,
	22, 868,
	262,972,
	262, 9137,
	431, 9138,
	428, 968,
	661, 868,
	666, 653,
	628, 655,
	661, 624,
	661, 510,
	589, 513,
	656, 462,
	661, 393,
	686, 358,
	685, 260,
	574, 396,
	569, 391,
	691, 247,
	682, 878
	};

	mapLimits.add(App->physics->CreateChain(0, 0, mapPoints1, 80));

	// Pivot 0, 0
	int mapPoints2[40] = {
	522, 365,
	558, 332,
	671, 197,
	683, 173,
	684, 138,
	664, 96,
	647, 79,
	609, 67,
	575, 65,
	553, 73,
	561, 75,
	580, 71,
	600, 71,
	622, 76,
	649, 89,
	663, 105,
	679, 136,
	679, 173,
	558, 326,
	517, 361
	};

	mapLimits.add(App->physics->CreateChain(0, 0, mapPoints2, 40));

	int mapPoints3[8] = {
	107, 308,
	90, 232,
	86, 248,
	101, 302
	};

	mapLimits.add(App->physics->CreateChain(0, 0, mapPoints3, 8));

	int mapPoints4[38] = {
	394, 90,
	392, 139,
	337, 138,
	290, 152,
	245, 185,
	231, 221,
	236, 260,
	259, 312,
	219, 238,
	189, 237,
	169, 259,
	168, 293,
	164, 294,
	114, 142,
	141, 116,
	180, 98,
	233, 89,
	303, 85,
	327, 78
	};

	mapLimits.add(App->physics->CreateChain(0, 0, mapPoints4, 38));

	int mapPoints5[30] = {
	302, 279,
	287, 249,
	286, 221,
	306, 196,
	336, 181,
	389, 179,
	382, 189,
	379, 224,
	375, 192,
	360, 187,
	340, 185,
	308, 199,
	289, 225,
	291, 246,
	309, 276
	};

	mapLimits.add(App->physics->CreateChain(0, 0, mapPoints5, 30));

	int mapPoints6[6] = {
	229, 824,
	169, 801,
	172, 731
	};

	mapLimits.add(App->physics->CreateChain(0, 0, mapPoints6, 6));

	int mapPoints7[6] = {
	474, 820,
	526, 797,
	526, 732
	};

	mapLimits.add(App->physics->CreateChain(0, 0, mapPoints7, 6));

	int mapPoints9[26] = {
	609, 202,
	633, 201,
	656, 188,
	664, 167,
	667, 133,
	670, 133,
	670, 164,
	664, 191,
	651, 208,
	640, 217,
	630, 225,
	623, 223,
	616, 210
	};

	mapLimits.add(App->physics->CreateChain(0, 0, mapPoints9, 26));

	int mapPoints8[24] = {
	341, 421,
	329, 421,
	328, 401,
	316, 386,
	298, 383,
	282, 385,
	272, 395,
	266, 387,
	285, 377,
	310, 375,
	329, 387,
	339, 400
	};

	//HAVE TO REPOSITION FLIPPERS 
	int RightFlipper[14] = {
		72, 5,
		65, 0,
		-36, 6,
		-40, 12,
		-34, 16,
		64, 18,
		72, 14
	};
	int LeftFlipper[14] = {
		0, 10,
		2, 3,
		10, 1,
		109, 6,
		112, 11,
		108, 17,
		5, 18
	};

	RightStickBody = App->physics->CreateFlipper(327, 882, RightFlipper, 14);
	LeftStickBody = App->physics->CreateFlipper(366, 882, LeftFlipper, 14);
	LeftStickAnchor = App->physics->CreateStaticCircle(223, 882, 3);
	RightStickAnchor = App->physics->CreateStaticCircle(466, 882, 3);

	bonusBall1 = App->physics->CreateCircle(320, 9999, 16);
	bonusBall2 = App->physics->CreateCircle(330, 9999, 16);
	bonusBall3 = App->physics->CreateCircle(330, 9999, 16);
	bonusBall4 = App->physics->CreateCircle(330, 9999, 16);
	bonusBall5 = App->physics->CreateCircle(330, 9999, 16);
	bonusBall6 = App->physics->CreateCircle(330, 9999, 16);


	App->physics->CreateFlipperJoints();


	mapLimits.add(App->physics->CreateChain(0, 0, mapPoints8, 24));
	
	//circles.add(App->physics->CreateCircle(712,814,18));
	
	bumpersBodys.add(App->physics->CreateStaticCircle(471, 294, 26));
	bumpersBodys.getLast()->data->listener = this;
	bumpersBodys.add(App->physics->CreateStaticCircle(465, 196, 26));
	bumpersBodys.getLast()->data->listener = this;
	bumpersBodys.add(App->physics->CreateStaticCircle(583, 228, 26));
	bumpersBodys.getLast()->data->listener = this;


	Bouncer = App->physics->CreateBouncer(715, 900, 54, 45);
	BouncerPivot = App->physics->CreateStaticCircle(710, 950, 3);

	App->physics->CreateBouncerJoint();

	/*
	App->player->player->body->DestroyFixture(App->player->player->body->GetFixtureList());
	App->player->createball = true;
	b2Filter b;
	b.categoryBits = ON;
	b.maskBits = ON | OFF;

	b.categoryBits = DISABLE;
	b.maskBits = DISABLE;
	*/

	if (score >= highScore)
	{
		highScore = score;
	}

	gameplayTimer = 218; // 218 to make it fit with music
	score = 0;

	App->player->createball = true;
	//App->player->player->body.getLast()->data->listener = this; <-- Al parecer no

	App->player->Enable();
	
	App->slowMotion = false;

	multiBallTimer = 0;
	eggTimer = 0;
	ringTimer = 0;

	delay = 0;
	delay2 = 0;
	delay3 = 0;

	return ret;
}

// Load assets
bool ModuleSceneGame::CleanUp()
{
	LOG("Unloading Game scene");
	//App->textures->Unload(basic_sprites);
	App->textures->Unload(circle);
	App->textures->Unload(GameScene);
	App->textures->Unload(RightStick);
	App->textures->Unload(LeftStick);
	App->textures->Unload(bumpers);
	App->textures->Unload(RightSlider);
	App->textures->Unload(LeftSlider);
	App->textures->Unload(FrontGameScene);

	App->textures->Unload(flecha1);
	App->textures->Unload(flecha2);
	App->textures->Unload(flecha3);
	App->textures->Unload(flecha4);
	App->textures->Unload(flecha5);
	App->textures->Unload(flecha6);
	App->textures->Unload(flecha7);
	App->textures->Unload(flecha8);
	App->textures->Unload(flecha9);
	App->textures->Unload(twoArrows1);
	App->textures->Unload(twoArrows2);
	App->textures->Unload(gge1);
	App->textures->Unload(gge2);
	App->textures->Unload(gge3);
	App->textures->Unload(digit1);
	App->textures->Unload(digit2);
	App->textures->Unload(digit3);
	App->textures->Unload(yellowArrows);
	App->textures->Unload(blueArrows);
	App->textures->Unload(numberTwo);
	App->textures->Unload(numberThree);
	App->textures->Unload(letterG);
	App->textures->Unload(lettersIN);
	App->textures->Unload(letterR);
	App->textures->Unload(circle2);
	App->textures->Unload(egg);
	App->textures->Unload(ring);
	App->textures->Unload(eggEffect);
	App->textures->Unload(ringEffect);
	App->textures->Unload(sceneUI);
	App->textures->Unload(multiBall);
	App->textures->Unload(contrast);
	App->textures->Unload(timeUp);
	App->textures->Unload(blueFourArrows);
	App->textures->Unload(yellowTwoArrows);
	App->textures->Unload(bouncer);

	App->scene_game->RightStickBody->body->DestroyFixture(App->scene_game->RightStickBody->body->GetFixtureList());
	App->scene_game->LeftStickBody->body->DestroyFixture(App->scene_game->LeftStickBody->body->GetFixtureList());

	App->scene_game->RightStickAnchor->body->DestroyFixture(App->scene_game->RightStickAnchor->body->GetFixtureList());
	App->scene_game->LeftStickAnchor->body->DestroyFixture(App->scene_game->LeftStickAnchor->body->GetFixtureList());

	App->scene_game->Bouncer->body->DestroyFixture(App->scene_game->Bouncer->body->GetFixtureList());
	App->scene_game->BouncerPivot->body->DestroyFixture(App->scene_game->BouncerPivot->body->GetFixtureList());

	App->scene_game->sensorLow->body->DestroyFixture(App->scene_game->sensorLow->body->GetFixtureList());

	//App->scene_game->RightSliderBody->body->DestroyFixture(App->scene_game->RightSliderBody->body->GetFixtureList());
	//App->scene_game->LeftSliderBody->body->DestroyFixture(App->scene_game->LeftSliderBody->body->GetFixtureList());

	App->scene_game->diamondSensor1->body->DestroyFixture(App->scene_game->diamondSensor1->body->GetFixtureList());
	App->scene_game->diamondSensor2->body->DestroyFixture(App->scene_game->diamondSensor2->body->GetFixtureList());
	App->scene_game->diamondSensor3->body->DestroyFixture(App->scene_game->diamondSensor3->body->GetFixtureList());
	App->scene_game->diamondSensor4->body->DestroyFixture(App->scene_game->diamondSensor4->body->GetFixtureList());
	App->scene_game->diamondSensor5->body->DestroyFixture(App->scene_game->diamondSensor5->body->GetFixtureList());
	App->scene_game->diamondSensor6->body->DestroyFixture(App->scene_game->diamondSensor6->body->GetFixtureList());
	App->scene_game->diamondSensorBig->body->DestroyFixture(App->scene_game->diamondSensorBig->body->GetFixtureList());

	App->scene_game->holeSensor1->body->DestroyFixture(App->scene_game->holeSensor1->body->GetFixtureList());
	App->scene_game->holeSensor2->body->DestroyFixture(App->scene_game->holeSensor2->body->GetFixtureList());
	App->scene_game->holeSensor3->body->DestroyFixture(App->scene_game->holeSensor3->body->GetFixtureList());

	App->scene_game->bonusBall1->body->DestroyFixture(App->scene_game->bonusBall1->body->GetFixtureList());
	App->scene_game->bonusBall2->body->DestroyFixture(App->scene_game->bonusBall2->body->GetFixtureList());
	App->scene_game->bonusBall3->body->DestroyFixture(App->scene_game->bonusBall3->body->GetFixtureList());
	App->scene_game->bonusBall4->body->DestroyFixture(App->scene_game->bonusBall4->body->GetFixtureList());
	App->scene_game->bonusBall5->body->DestroyFixture(App->scene_game->bonusBall5->body->GetFixtureList());
	App->scene_game->bonusBall6->body->DestroyFixture(App->scene_game->bonusBall6->body->GetFixtureList());

	App->scene_game->multiBallSensor->body->DestroyFixture(App->scene_game->multiBallSensor->body->GetFixtureList());
	App->scene_game->eggSensor->body->DestroyFixture(App->scene_game->eggSensor->body->GetFixtureList());
	App->scene_game->ringSensor->body->DestroyFixture(App->scene_game->ringSensor->body->GetFixtureList());

	//Esto para los circles y los bumpers también
	p2List_item<PhysBody*>* chains;
	int i = 0;

	for (chains = App->scene_game->mapLimits.getFirst(); i < mapLimits.count(); i++)
	{
		if (chains->data->body->GetFixtureList() != nullptr)
		{
			chains->data->body->DestroyFixture(chains->data->body->GetFixtureList());
		}
		
		chains->next; // Esta instrucción se la salta porque le da la gana y por lo tanto no puede iterar correctamente y no se borran todas las cosas
	}
	
	return true;
}

// Update: draw background
update_status ModuleSceneGame::Update()
{
	Mix_VolumeMusic(56);
	//Mix_Volume(1, 16);

	if ((delay % 60) == 0)
	{
		/*
		if (timeCounter <= 0)
		{
			timeCounter == 0;
		}
		*/
		gameplayTimer--;
	}
	delay++;

	App->renderer->Blit(GameScene, 0, 0, NULL, 1.0f, NULL);

	if (delay > 10)
	{
		delay2++;
	}
	if (delay2 > 20)
	{
		delay3++;
	}

	if ((delay / 60) % 2 == 0) App->renderer->Blit(flecha1, 0, 0, NULL, 1.0f, NULL);
	if ((delay2 / 60) % 2 == 0) App->renderer->Blit(flecha2, 0, 0, NULL, 1.0f, NULL);
	if ((delay3 / 60) % 2 == 0) App->renderer->Blit(flecha3, 0, 0, NULL, 1.0f, NULL);

	if ((delay / 60) % 2 == 0 && multiBallActive == false && ringActive == false && eggActive == false) App->renderer->Blit(flecha4, 0, 0, NULL, 1.0f, NULL);
	if ((delay2 / 60) % 2 == 0 && multiBallActive == false && ringActive == false && eggActive == false) App->renderer->Blit(flecha5, 0, 0, NULL, 1.0f, NULL);
	if ((delay3 / 60) % 2 == 0 && multiBallActive == false && ringActive == false && eggActive == false) App->renderer->Blit(flecha6, 0, 0, NULL, 1.0f, NULL);

	if ((delay / 60) % 2 == 0) App->renderer->Blit(flecha7, 0, 0, NULL, 1.0f, NULL);
	if ((delay2 / 60) % 2 == 0) App->renderer->Blit(flecha8, 0, 0, NULL, 1.0f, NULL);
	if ((delay3 / 60) % 2 == 0) App->renderer->Blit(flecha9, 0, 0, NULL, 1.0f, NULL);

	if ((delay3 / 60) % 2 == 0 && multiBallActive == false && ringActive == false && eggActive == false) App->renderer->Blit(gge1, 0, 0, NULL, 1.0f, NULL);
	if ((delay2 / 60) % 2 == 0 && multiBallActive == false && ringActive == false && eggActive == false) App->renderer->Blit(gge2, 0, 0, NULL, 1.0f, NULL);
	if ((delay / 60) % 2 == 0 && multiBallActive == false && ringActive == false && eggActive == false) App->renderer->Blit(gge3, 0, 0, NULL, 1.0f, NULL);

	if ((delay / 60) % 2 == 0 && multiBallActive == false && ringActive == false && eggActive == false) App->renderer->Blit(twoArrows1, 0, 0, NULL, 1.0f, NULL);
	if ((delay2 / 60) % 2 == 0 && multiBallActive == false && ringActive == false && eggActive == false) App->renderer->Blit(twoArrows2, 0, 0, NULL, 1.0f, NULL);

	if ((delay3 / 120) % 2 == 0) App->renderer->Blit(digit1, 0, 0, NULL, 1.0f, NULL);
	if ((delay2 / 120) % 2 == 0) App->renderer->Blit(digit2, 0, 0, NULL, 1.0f, NULL);
	if ((delay / 120) % 2 == 0) App->renderer->Blit(digit3, 0, 0, NULL, 1.0f, NULL);

	if ((delay / 60) % 2 == 0) App->renderer->Blit(blueArrows, 0, 0, NULL, 1.0f, NULL);
	if ((delay2 / 120) % 2 == 0) App->renderer->Blit(yellowArrows, 0, 0, NULL, 1.0f, NULL);

	if ((delay / 60) % 2 == 0) App->renderer->Blit(numberTwo, 0, 0, NULL, 1.0f, NULL);
	if ((delay2 / 60) % 2 == 0) App->renderer->Blit(numberThree, 0, 0, NULL, 1.0f, NULL);

	if ((delay3 / 60) % 2 == 0 && multiBallActive == false && ringActive == false && eggActive == false) App->renderer->Blit(letterG, 0, 0, NULL, 1.0f, NULL);
	if ((delay2 / 60) % 2 == 0 && multiBallActive == false && ringActive == false && eggActive == false) App->renderer->Blit(lettersIN, 0, 0, NULL, 1.0f, NULL);
	if ((delay / 60) % 2 == 0 && multiBallActive == false && ringActive == false && eggActive == false) App->renderer->Blit(letterR, 0, 0, NULL, 1.0f, NULL);

	if ((delay / 60) % 2 == 0) App->renderer->Blit(blueFourArrows, 0, 0, NULL, 1.0f, NULL);
	if ((delay2 / 120) % 2 == 0) App->renderer->Blit(yellowTwoArrows, 0, 0, NULL, 1.0f, NULL);

	//App->renderer->Blit(LeftStick, 366, 882, NULL, 0.0f,LeftStickBody->body->GetAngle());
	//App->renderer->Blit(RightStick, 327, 882, NULL, 0.0f, RightStickBody->body->GetAngle());


	//Bonus balls
	bonusBall1->GetPosition(bonusBall1PositionX, bonusBall1PositionY);
	App->renderer->Blit(circle2, bonusBall1PositionX, bonusBall1PositionY, NULL, 1.0f, bonusBall1->GetRotation());

	bonusBall2->GetPosition(bonusBall2PositionX, bonusBall2PositionY);
	App->renderer->Blit(circle2, bonusBall2PositionX, bonusBall2PositionY, NULL, 1.0f, bonusBall2->GetRotation());

	bonusBall3->GetPosition(bonusBall3PositionX, bonusBall3PositionY);
	App->renderer->Blit(circle2, bonusBall3PositionX, bonusBall3PositionY, NULL, 1.0f, bonusBall3->GetRotation());

	bonusBall4->GetPosition(bonusBall4PositionX, bonusBall4PositionY);
	App->renderer->Blit(circle2, bonusBall4PositionX, bonusBall4PositionY, NULL, 1.0f, bonusBall4->GetRotation());

	bonusBall5->GetPosition(bonusBall5PositionX, bonusBall5PositionY);
	App->renderer->Blit(circle2, bonusBall5PositionX, bonusBall5PositionY, NULL, 1.0f, bonusBall5->GetRotation());

	bonusBall6->GetPosition(bonusBall6PositionX, bonusBall6PositionY);
	App->renderer->Blit(circle2, bonusBall6PositionX, bonusBall6PositionY, NULL, 1.0f, bonusBall6->GetRotation());

	RightStickBody->GetPosition(RightStickPosX, RightStickPosY);
	App->renderer->Blit(RightStick, RightStickPosX - 35, RightStickPosY - 56, NULL, 1.0f, RightStickBody->GetRotation() + 20, 30, 50);

	LeftStickBody->GetPosition(LeftStickPosX, LeftStickPosY);
	App->renderer->Blit(LeftStick, LeftStickPosX - 10, LeftStickPosY - 30, NULL, 1.0f, LeftStickBody->GetRotation() - 20, 10, 20);

	Bouncer->GetPosition(bouncerPositionX, bouncerPositionY);
	App->renderer->Blit(bouncer, bouncerPositionX, bouncerPositionY, NULL, 1.0f, Bouncer->GetRotation());

	/*
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 18));
		circles.getLast()->data->listener = this;
		//App->player->createball = true;
	}
	*/
	
	/*
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
	{
		//Add bouncer impulse
		Bouncer->body->ApplyForce({ 0,-350 }, { 0,0 }, true);

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
		{
			Bouncer->body->ApplyForce({ 0,350 }, { 0,0 }, true);
		}
	}
	*/

	if ((delay % 120) == 0 && eggActive == true)
	{
		Bouncer->body->ApplyForce({ 0,-2000 }, { 0,0 }, true);
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN && eggActive == false)
	{
		//Add bouncer impulse
		Bouncer->body->ApplyForce({ 0,-2000 }, { 0,0 }, true);

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
		{
			//Bouncer->body->ApplyForce({ 0,500 }, { 0,0 }, true);
		}
	}
	
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		LeftStickBody->body->ApplyForce({ 5,150 }, { 0,0 }, true);

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
		{
			//LeftStickBody->body->ApplyForce({ -5,-60 }, { 0,0 }, true);
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		RightStickBody->body->ApplyForce({ -5,-60 }, { 0,0 }, true);

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
		{
			//RightStickBody->body->ApplyForce({ 5,-60 }, { 0,0 }, true);
		}
	}
	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	App->renderer->Blit(FrontGameScene, 0, 0, NULL, 1.0f, NULL);

	if (multiBallActive == true)
	{
		multiBallTimer++;

		if (multiBallTimer >= 1 && multiBallTimer <= 90)
		{
			App->renderer->Blit(contrast, 0, 0, NULL, 1.0f, NULL);
			App->renderer->Blit(multiBall, 190, 390, NULL, 1.0f, NULL);
		}

		if (multiBallTimer > 90 && multiBallTimer <= 91)
		{
			bonusBall1 = App->physics->CreateCircle(130, 460, 16);
			bonusBall2 = App->physics->CreateCircle(350, 550, 16);
			bonusBall3 = App->physics->CreateCircle(450, 350, 16);
			bonusBall4 = App->physics->CreateCircle(300, 640, 16);
			bonusBall5 = App->physics->CreateCircle(380, 264, 16);
			bonusBall6 = App->physics->CreateCircle(330, 560, 16);
		}

		if (multiBallTimer > 900 || gameplayTimer <= 2)
		{
			multiBallTimer = 0;
			multiBallActive = false;
		}
	}

	if (eggActive == true)
	{
		eggTimer++;

		if (eggTimer >= 1 && eggTimer <= 90)
		{
			App->renderer->Blit(contrast, 0, 0, NULL, 1.0f, NULL);
			App->renderer->Blit(egg, 190, 390, NULL, 1.0f, NULL);
		}

		App->renderer->Blit(eggEffect, 0, 0, NULL, 1.0f, NULL);

		scoreChanger = -1;

		if (eggTimer > 900 || gameplayTimer <= 2)
		{
			scoreChanger = 1;
			eggTimer = 0;
			eggActive = false;
		}
	}

	if (ringActive == true)
	{
		ringTimer++;

		if (ringTimer >= 1 && ringTimer <= 90)
		{
			App->renderer->Blit(contrast, 0, 0, NULL, 1.0f, NULL);
			App->renderer->Blit(ring, 190, 390, NULL, 1.0f, NULL);
		}

		App->renderer->Blit(ringEffect, 0, 0, NULL, 1.0f, NULL);

		scoreChanger = 2;

		if (ringTimer > 900 || gameplayTimer <= 2)
		{
			scoreChanger = 1;
			ringTimer = 0;
			ringActive = false;
		}
	}

	if (gameplayTimer <= 0)
	{
		App->renderer->Blit(contrast, 0, 0, NULL, 1.0f, NULL);
		App->renderer->Blit(timeUp, (SCREEN_WIDTH / 2) - (560 / 2), (SCREEN_HEIGHT / 2) - (260 / 2), NULL, 1.0f, NULL);
		
		if (gameplayTimer < -2)
		{
			Mix_PauseMusic();
			App->player->Disable();
			App->fade->FadeToBlack((Module*)App->scene_game, (Module*)App->scene_intro, 90);
		}
	}

	App->renderer->Blit(sceneUI, 0, 0, NULL, 1.0f, NULL);

	// Timer
	//App->fonts->BlitText(180, 10, timeFont, timeText);
	sprintf_s(timeText, 10, "%3d", gameplayTimer);
	if(gameplayTimer >= 0) App->fonts->BlitText(60, 10, timeFont, timeText);

	sprintf_s(timeText, 10, "%4d", score);
	App->fonts->BlitText(200, 10, timeFont, timeText);

	sprintf_s(timeText, 10, "%4d", highScore);
	App->fonts->BlitText(415, 10, timeFont, timeText);

	if (score < 0) score = 0;

	return UPDATE_CONTINUE;
}

void ModuleSceneGame::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	//int x, y;
	

	if (bodyA != nullptr && bodyB != nullptr)
	{
		b2Filter filter;
		filter.categoryBits = 0x0001;
		filter.maskBits = 0x0001;

	/*
	if (bodyA)
		{
			bodyA->GetPosition(x, y);
			App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
		}

		if (bodyB)
		{
			bodyB->GetPosition(x, y);
			App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
		}
	*/

		if (bodyA->body == App->player->player->body && bodyB->body == sensorLow->body)
		{
			if (gameplayTimer > 0)
			{
				filter.categoryBits = 0x0002;
				filter.maskBits = 0x0002 | 0x0001;

				b2Vec2 position;
				position.x = 688;
				position.y = 820;

				score = score - 50;

				LOG("Player Collision");
				App->player->player->body->GetFixtureList()->SetFilterData(filter);
				App->player->createball = true;
			}
		}
		if (bodyA->body == App->player->player->body && (bodyB->body == holeSensor1->body || bodyB->body == holeSensor2->body || bodyB->body == holeSensor3->body))
		{
			if (gameplayTimer > 0)
			{
				filter.categoryBits = 0x0002;
				filter.maskBits = 0x0002 | 0x0001;

				b2Vec2 position;
				position.x = 688;
				position.y = 820;

				score = score + 150 * scoreChanger;

				LOG("Player Collision");
				App->player->player->body->GetFixtureList()->SetFilterData(filter);
				//App->player->player->body->DestroyFixture(App->player->player->body->GetFixtureList());
				App->player->createball = true;

				if (eggActive == false) App->audio->PlayFx(bonus_fx);
				//if (eggActive == true) App->audio->PlayFx(bonusOp_fx);
			}
		}
		
		if (bodyA->body == App->player->player->body && (bodyB->body == diamondSensor1->body || bodyB->body == diamondSensor2->body || bodyB->body == diamondSensor3->body ||
			bodyB->body == diamondSensor4->body || bodyB->body == diamondSensor5->body || bodyB->body == diamondSensor6->body))
		{
			if (gameplayTimer > 0)
			{

				score = score + 3 * scoreChanger;

				LOG("Player Collision");

				if (eggActive == false) App->audio->PlayFx(bonus_fx);
				//if (eggActive == true) App->audio->PlayFx(bonusOp_fx);
			}
		}

		if (bodyA->body == App->player->player->body && bodyB->body == App->scene_game->diamondSensorBig->body)
		{
			if (gameplayTimer > 0)
			{

				score = score + 5 * scoreChanger;

				LOG("Player Collision");

				if (eggActive == false) App->audio->PlayFx(bonus_fx);
				//if (eggActive == true) App->audio->PlayFx(bonusOp_fx);
			}
		}

		if ((bodyA->body == App->scene_game->bonusBall1->body || bodyA->body == App->scene_game->bonusBall2->body || bodyA->body == App->scene_game->bonusBall3->body
			|| bodyA->body == App->scene_game->bonusBall4->body || bodyA->body == App->scene_game->bonusBall5->body || bodyA->body == App->scene_game->bonusBall6->body)
			&& (bodyB->body == diamondSensor1->body || bodyB->body == diamondSensor2->body || bodyB->body == diamondSensor3->body ||
				bodyB->body == diamondSensor4->body || bodyB->body == diamondSensor5->body || bodyB->body == diamondSensor6->body))
		{
			if (gameplayTimer > 0)
			{

				score = score + 3 * scoreChanger;

				LOG("Player Collision");

				if (eggActive == false) App->audio->PlayFx(bonus_fx);
				//if (eggActive == true) App->audio->PlayFx(bonusOp_fx);
			}
		}

		if ((bodyA->body == App->scene_game->bonusBall1->body || bodyA->body == App->scene_game->bonusBall2->body || bodyA->body == App->scene_game->bonusBall3->body
			|| bodyA->body == App->scene_game->bonusBall4->body || bodyA->body == App->scene_game->bonusBall5->body || bodyA->body == App->scene_game->bonusBall6->body)
			&& bodyB->body == diamondSensorBig->body)
		{
			if (gameplayTimer > 0)
			{

				score = score + 5 * scoreChanger;

				LOG("Player Collision");

				if (eggActive == false) App->audio->PlayFx(bonus_fx);
				//if (eggActive == true) App->audio->PlayFx(bonusOp_fx);
			}
		}
	}

	if (bodyA->body == App->player->player->body && bodyB->body == App->scene_game->multiBallSensor->body && multiBallActive == false && ringActive == false && eggActive == false)
	{
		if (gameplayTimer > 0)
		{
			multiBallActive = true;

			LOG("Player Collision");
			App->player->createball = true;

			App->audio->PlayFx(multiBall_fx);
		}
	}

	if (bodyA->body == App->player->player->body && bodyB->body == App->scene_game->eggSensor->body && eggActive == false && ringActive == false)
	{
		if (gameplayTimer > 0)
		{
			eggActive = true;

			LOG("Player Collision");
			App->player->createball = true;

			App->audio->PlayFx(egg_fx);
		}
	}

	if (bodyA->body == App->player->player->body && bodyB->body == App->scene_game->ringSensor->body && ringActive == false && eggActive == false)
	{
		if (gameplayTimer > 0)
		{
			ringActive = true;

			LOG("Player Collision");
			App->player->createball = true;

			App->audio->PlayFx(multiBall_fx);
		}
	}
}
