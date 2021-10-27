#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleSceneGame.h"
#include "ModuleTextures.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"

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
	player->GetPosition(playerX, playerY);
	App->renderer->Blit(graphics, playerX, playerY, NULL, 1.0f, player->GetRotation());


	return UPDATE_CONTINUE;
}



