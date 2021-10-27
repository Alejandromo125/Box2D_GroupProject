#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneGame.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "p2List.h"
#include "p2Point.h"
#include "ModulePlayer.h"


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
	RightStick = App->textures->Load("pinball/R - Stick x52.png");
	LeftStick = App->textures->Load("pinball/L - Stick x52.png");
	bumpers = App->textures->Load("pinball/Obstacle-1.png");
	RightSlider = App->textures->Load("pinball/R - Object2.png");
	LeftSlider = App->textures->Load("pinball/L - Object2.png");

	flecha1 = App->textures->Load("pinball/flecha1.png");
	flecha2 = App->textures->Load("pinball/flecha2.png");
	flecha3 = App->textures->Load("pinball/flecha3.png");
	flecha4 = App->textures->Load("pinball/flecha4.png");
	flecha5 = App->textures->Load("pinball/flecha5.png");
	flecha6 = App->textures->Load("pinball/flecha6.png");
	flecha7 = App->textures->Load("pinball/flecha7.png");
	flecha8 = App->textures->Load("pinball/flecha8.png");
	flecha9 = App->textures->Load("pinball/flecha9.png");

	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");



	sensorLow = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 10);
	sensorLow->listener = this;
	sensorLow->body->GetFixtureList()->SetFilterData(filter);
	
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
	262, 1137,
	431, 1138,
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
		2, 6,
		0, 12,
		4, 16,
		64, 18,
		72, 14
	};
	int LeftFlipper[14] = {
		0, 10,
		2, 3,
		10, 1,
		69, 6,
		72, 11,
		68, 17,
		5, 18
	};

	RightStickBody = App->physics->CreateFlipper(327, 457, RightFlipper, 14);
	LeftStickBody = App->physics->CreateFlipper(366, 882, LeftFlipper, 14);
	LeftStickAnchor = App->physics->CreateStaticCircle(223, 882, 3);
	RightStickAnchor = App->physics->CreateStaticCircle(466, 882, 3);

	App->physics->CreateFlipperJoints();


	mapLimits.add(App->physics->CreateChain(0, 0, mapPoints8, 24));
	
	circles.add(App->physics->CreateCircle(712,814,18));
	circles.getLast()->data->listener = this;
	
	bumpersBodys.add(App->physics->CreateStaticCircle(452, 286, 26));
	bumpersBodys.getLast()->data->listener = this;
	bumpersBodys.add(App->physics->CreateStaticCircle(352, 286, 26));
	bumpersBodys.getLast()->data->listener = this;
	bumpersBodys.add(App->physics->CreateStaticCircle(252, 286, 26));
	bumpersBodys.getLast()->data->listener = this;



	Bouncer = App->physics->CreateBouncer(715, 900, 54, 45);
	BouncerPivot = App->physics->CreateStaticCircle(710, 950, 3);

	App->physics->CreateBouncerJoint();

	delay = 0;
	delay2 = 0;
	delay3 = 0;

	return ret;
}

// Load assets
bool ModuleSceneGame::CleanUp()
{
	LOG("Unloading Game scene");

	return true;
}

// Update: draw background
update_status ModuleSceneGame::Update()
{
	
	delay++;

	App->renderer->Blit(GameScene, 0, 0, NULL, 1.0f, NULL);

	App->renderer->Blit(LeftStick, LeftStickBody->body->GetPosition().x, LeftStickBody->body->GetPosition().y, NULL, 0.0f);
	App->renderer->Blit(LeftStick, RightStickBody->body->GetPosition().x, RightStickBody->body->GetPosition().y, NULL, 0.0f);

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

	if ((delay / 60) % 2 == 0) App->renderer->Blit(flecha4, 0, 0, NULL, 1.0f, NULL);
	if ((delay2 / 60) % 2 == 0) App->renderer->Blit(flecha5, 0, 0, NULL, 1.0f, NULL);
	if ((delay3 / 60) % 2 == 0) App->renderer->Blit(flecha6, 0, 0, NULL, 1.0f, NULL);

	if ((delay / 60) % 2 == 0) App->renderer->Blit(flecha7, 0, 0, NULL, 1.0f, NULL);
	if ((delay2 / 60) % 2 == 0) App->renderer->Blit(flecha8, 0, 0, NULL, 1.0f, NULL);
	if ((delay3 / 60) % 2 == 0) App->renderer->Blit(flecha9, 0, 0, NULL, 1.0f, NULL);

	
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 18));
		circles.getLast()->data->listener = this;
		
	}
	
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN)
	{
		//Add bouncer impulse
		Bouncer->body->ApplyForce({ 0,-350 }, { 0,0 }, true);

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
		{
			Bouncer->body->ApplyForce({ 0,350 }, { 0,0 }, true);
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		//Add bouncer impulse
		Bouncer->body->ApplyForce({ 0,-500 }, { 0,0 }, true);

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
		{
			Bouncer->body->ApplyForce({ 0,500 }, { 0,0 }, true);
		}
	}
	
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		LeftStickBody->body->ApplyForce({ 5,60 }, { 0,0 }, true);

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
		{
			LeftStickBody->body->ApplyForce({ -5,-60 }, { 0,0 }, true);
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


	return UPDATE_CONTINUE;
}

void ModuleSceneGame::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;
	
	App->audio->PlayFx(bonus_fx);

	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if (bodyA->body == App->player->player->body && bodyB->body == sensorLow->body)
	{
		
	}
	*/
}
