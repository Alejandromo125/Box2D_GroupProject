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
