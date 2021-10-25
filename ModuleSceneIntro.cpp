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

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	App->renderer->DrawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 50, 255, 0, 0, 0, true);
	
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

	if (App->input->GetKey(SDL_SCANCODE_SPACE)==KEY_DOWN)
	{
		if (App->scene_game->IsEnabled() == false)
		{
			App->scene_game->Enable();
		}
		
		App->fade->FadeToBlack(this, (Module*)App->scene_game, 90);
	}

	return UPDATE_CONTINUE;
}

