#include "Application.h"
#include "ModuleSceneIntroAbove.h"

ModuleSceneIntroAbove::ModuleSceneIntroAbove(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleSceneIntroAbove::~ModuleSceneIntroAbove()
{}

// Load assets
bool ModuleSceneIntroAbove::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	// Bumpers 
	Freezer = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Bumper_Freezer.png");
	Babidi = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Bumper_Babidi.png");
	Cell = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Bumper_Cell.png");
	Buu = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Bumper_Buu.png");
	// Top house & ship
	kame_house_top = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Top_House_02.png");
	ship_top = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Top_Ship_02.png");
	// Bean
	bean_tex = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Balls_Magic_Bean_Hit.png");

	return ret;
}

// Update: draw Above Player
update_status ModuleSceneIntroAbove::Update()
{
	App->renderer->Blit(Freezer, 297, 217);
	App->renderer->Blit(Babidi, 303, 122);
	App->renderer->Blit(Cell, 365, 165);
	App->renderer->Blit(Buu, 227, 155);

	App->renderer->Blit(ship_top, 470, 101);
	App->renderer->Blit(kame_house_top, 28, 501);

	// Draw in case of contact
	if (App->scene_intro->magic_bean.hit_timer > 0)
	{
		if (SDL_TICKS_PASSED(SDL_GetTicks(), App->scene_intro->magic_bean.hit_timer) == false)
		{
			App->renderer->Blit(bean_tex, 112, 122);
			LOG("Drawing Bean!");
		}
		else
		{
			App->scene_intro->magic_bean.hit_timer = 0;
		}
	}

	if (App->scene_intro->bumper1.hit_timer > 0)
	{
		if (SDL_TICKS_PASSED(SDL_GetTicks(), App->scene_intro->bumper1.hit_timer) == false)
			App->renderer->Blit(App->scene_intro->bumper1.texture, 227, 155);
		else
		{
			App->scene_intro->bumper1.hit_timer = 0;
		}
	}

	if (App->scene_intro->bumper2.hit_timer > 0)
	{
		if (SDL_TICKS_PASSED(SDL_GetTicks(), App->scene_intro->bumper2.hit_timer) == false)
			App->renderer->Blit(App->scene_intro->bumper2.texture, 297, 217);
		else
		{
			App->scene_intro->bumper2.hit_timer = 0;
		}
	}

	if (App->scene_intro->bumper3.hit_timer > 0)
	{
		if (SDL_TICKS_PASSED(SDL_GetTicks(), App->scene_intro->bumper3.hit_timer) == false)
			App->renderer->Blit(App->scene_intro->bumper3.texture, 303, 122);
		else
		{
			App->scene_intro->bumper3.hit_timer = 0;
		}
	}

	if (App->scene_intro->bumper4.hit_timer > 0)
	{
		if (SDL_TICKS_PASSED(SDL_GetTicks(), App->scene_intro->bumper4.hit_timer) == false)
			App->renderer->Blit(App->scene_intro->bumper4.texture, 365, 165);
		else
		{
			App->scene_intro->bumper4.hit_timer = 0;
		}
	}

	if (App->scene_intro->bumper_left.hit_timer > 0)
	{
		if (SDL_TICKS_PASSED(SDL_GetTicks(), App->scene_intro->bumper_left.hit_timer) == false)
			App->renderer->Blit(App->scene_intro->bumper_left.texture, 145, 785);
		else
		{
			App->scene_intro->bumper_left.hit_timer = 0;
		}
	}

	if (App->scene_intro->bumper_right.hit_timer > 0)
	{
		if (SDL_TICKS_PASSED(SDL_GetTicks(), App->scene_intro->bumper_right.hit_timer) == false)
			App->renderer->Blit(App->scene_intro->bumper_right.texture, 425, 785);
		else
		{
			App->scene_intro->bumper_right.hit_timer = 0;
		}
	}

	return UPDATE_CONTINUE;
}

// Load assets
bool ModuleSceneIntroAbove::CleanUp()
{
	LOG("Unloading Intro scene");
	
	App->textures->Unload(Freezer);
	App->textures->Unload(Babidi);
	App->textures->Unload(Cell);
	App->textures->Unload(Buu);
	App->textures->Unload(kame_house_top);
	App->textures->Unload(ship_top);
	App->textures->Unload(bean_tex);

	return true;
}