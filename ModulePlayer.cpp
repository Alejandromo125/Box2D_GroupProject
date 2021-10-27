#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePhysics.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "ModuleSceneGame.h"
#include "ModuleAudio.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("pinball/sonic_ball.png");
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if (createball == true)
	{
		//App->audio->PlayFx(ball_spawn_sound);
		player = App->physics->CreateCircle(354, 311, 8);
		player->listener = App->scene_game;
		b2Filter b;
		b.categoryBits = 0x0001;
		b.maskBits = 0x0001 | 0x0002;
		player->body->GetFixtureList()->SetFilterData(b);
		createball = false;
	}

	player->body->SetBullet(true);

	if ((player->body->GetPosition().x > 364) && (player->body->GetPosition().y > 280)) //sets restitution only if ball has departed
	{
		player->body->GetFixtureList()->SetRestitution(0.3);
	}

	int playerPositionX, playerPositionY;
	player->GetPosition(playerPositionX, playerPositionY);
	App->renderer->Blit(graphics, playerPositionX, playerPositionY, NULL, 1.0f, player->GetRotation());


	return UPDATE_CONTINUE;
}



