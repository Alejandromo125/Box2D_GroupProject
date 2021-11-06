#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneGame.h"
#include "ModulePlayer.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	introLogo = NULL;
	startButton = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	introLogo = App->textures->Load("pinball/introbg.png");
	startButton = App->textures->Load("pinball/startButton.png");

	App->audio->PlayMusic("pinball/introMusic.ogg", 0.0f);

	delay = 0;

	//App->player->Disable();
	//App->scene_game->Disable();

	//App->player->createball = false;
	
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	delay++;
	//Mix_PauseMusic(); Intro Music
		
	App->renderer->Blit(introLogo, 0, 0, NULL, 1.0f,NULL);

	if((delay / 30) % 2 == 0)
	{
		App->renderer->Blit(startButton, 90, 700, NULL, 1.0f, NULL);
	}
	
		
	if (App->input->GetKey(SDL_SCANCODE_SPACE)==KEY_DOWN)
	{
		if (App->scene_game->IsEnabled() == false)
		{
			App->scene_game->Enable();
		}
		if (App->player->IsEnabled() == false)
		{
			App->player->Enable();
		}
		App->scene_intro->Disable();
		
		App->fade->FadeToBlack((Module*)App->scene_intro, (Module*)App->scene_game, 90);
	}


	return UPDATE_CONTINUE;
}

