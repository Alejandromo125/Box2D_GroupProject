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
	
	int mapPoints[72] = {
		634,948,
		634,854,
		416,970,
		416,1200,
		284,1200,
		284,970,
		86,873,
		86,707,
		101,684,
		116,672,
		157,657,
		161,647,
		98,566,
		98,547,
		105,539,
		120,533,
		157,566,
		150,464,
		134,427,
		98,296,
		93,212,
		110,137,
		143,90,
		197,52,
		281,32,
		431,42,
		550,66,
		622,97,
		608,59,
		596,36,
		610,16,
		627,15,
		649,35,
		667,79,
		673,133,
		670,948,
	};

	mapLimits.add(App->physics->CreateChain(0, 0, mapPoints, 72));
	
	circles.add(App->physics->CreateCircle(652,937,18));
	circles.getLast()->data->listener = this;
	

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

	bumpersBodys.add(App->physics->CreateBumper(452,286,26));
	bumpersBodys.add(App->physics->CreateBumper(452, 286, 26));
	bumpersBodys.add(App->physics->CreateBumper(452, 286, 26));

	

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
