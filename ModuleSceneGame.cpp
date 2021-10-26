#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneGame.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneGame::ModuleSceneGame(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = NULL;
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
	
	App->renderer->camera.x = App->renderer->camera.y = 0;

	GameScene = App->textures->Load("pinball/sceneGame.png");
	circle = App->textures->Load("pinball/sonic_ball.png");
	RightStick = App->textures->Load("pinball/R - Stick x52.png");
	LeftStick = App->textures->Load("pinball/L - Stick x52.png");
	bumpers = App->textures->Load("pinball/Obstacle-1.png");
	RightSlider = App->textures->Load("pinball/R - Object2.png");
	LeftSlider = App->textures->Load("pinball/L - Object2.png");

	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 10);
	
	int mapPoints1[88] = {
	685, 897,
	740, 895,
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
	97, 714,
	98, 828,
	240, 878,
	240, 897,
	262, 906,
	262, 1137,
	431, 1138,
	428, 907,
	454, 893,
	661, 800,
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

	mapLimits.add(App->physics->CreateChain(0, 0, mapPoints1, 88));

	// Pivot 0, 0
	int mapPoints2[36] = {
		519, 362,
		559, 331,
		679, 189,
		685, 147,
		670, 104,
		644, 77,
		613, 66,
		581, 61,
		551, 65,
		554, 70,
		580, 65,
		611, 69,
		642, 81,
		665, 106,
		680, 143,
		675, 189,
		556, 328,
		520, 352
	};

	mapLimits.add(App->physics->CreateChain(0, 0, mapPoints2, 36));

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

	mapLimits.add(App->physics->CreateChain(0, 0, mapPoints8, 24));
	
	circles.add(App->physics->CreateCircle(652,937,18));
	circles.getLast()->data->listener = this;
	
	bumpersBodys.add(App->physics->CreateBumper(452, 286, 26));

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
	App->renderer->Blit(GameScene, 0, 0, NULL, 1.0f, NULL);
	

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 18));
		circles.getLast()->data->listener = this;
		
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
	
}
