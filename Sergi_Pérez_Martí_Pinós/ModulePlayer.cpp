#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	// Lose & restart fx
	lose_fx = App->audio->LoadFx("pinball/Dragon_Pin_Ball_Fx/DB - Death Sound_-15.wav");
	restart_fx = App->audio->LoadFx("pinball/Dragon_Pin_Ball_Fx/DB - Death for sure_-20.wav");

	// Balls
	ball_tex4 = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Balls_Dragon_Ball_04.png");
	ball = CreateBallz(650, 700);

	// Launcher
	launcher_tex = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Launcher.png");
	launcher_fx = App->audio->LoadFx("pinball/Dragon_Pin_Ball_Fx/DB - Punch Heavy01_-20.wav");

	CreateLauncher();

	// Flippers
	int flipp1_points[16] = 
	{
		13, 1,
		1, 7,
		1, 19,
		12, 27,
		108, 22,
		115, 15,
		115, 10,
		108, 4
	};

	flipper1 = CreateFlipper(188, 1013, 5, flipp1_points, 16, 1);

	int flipp2_points[16] =
	{
		104, 1,
		116, 7,
		116, 19,
		105, 27,
		9, 22,
		2, 15,
		2, 10,
		9, 4
	};

	flipper2 = CreateFlipper(459, 1013, 5, flipp2_points, 16, 2);

	int flipp3_points[16] =
	{
		8, 1,
		1, 7,
		1, 18,
		11, 23,
		78, 19,
		83, 14,
		83, 8,
		77, 4
	};

	flipper3 = CreateFlipper( 86, 330, 5, flipp3_points, 16, 3);

	int flipp4_points[16] =
	{
		77, 1,
		84, 7,
		84, 19,
		73, 27,
		7, 22,
		2, 15,
		2, 10,
		8, 4
	};

	flipper4 = CreateFlipper( 550, 505, 5, flipp4_points, 16, 4);

	flipper1->paddle_texture = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Flipper01.png");
	flipper2->paddle_texture = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Flipper02.png");
	flipper3->paddle_texture = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Flipper_Little_01.png");
	flipper4->paddle_texture = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Flipper_Little_02.png");

	flipper1->fx = flipper2->fx = flipper3->fx = flipper4->fx = App->audio->LoadFx("pinball/Dragon_Pin_Ball_Fx/DB - Combo02_-20.wav");
	
	App->physics->CreateRevoluteJoint(flipper1->flipper_support->body, flipper1->flipper_paddle->body, 0, 0, 10, 10, 0, 25, -15, 100);
	App->physics->CreateRevoluteJoint(flipper2->flipper_support->body, flipper2->flipper_paddle->body, 0, 0, 107, 10, 0, 15, -25, -100);
	App->physics->CreateRevoluteJoint(flipper3->flipper_support->body, flipper3->flipper_paddle->body, 0, 0, 10, 10, 0, 85, 20, 100);
	App->physics->CreateRevoluteJoint(flipper4->flipper_support->body, flipper4->flipper_paddle->body, 0, 0, 75, 10, 0, 10, -65, -100);

	return true;
}

update_status ModulePlayer::Update()
{
	// Update title with score
	char title[70];
	sprintf_s(title, "Dragon Ballz: %d  /  Score: %06d  /  Last Score: %06d", lives, score, last_score);
	App->window->SetTitle(title);

	// Inputs -------------------------------------
	// Left Flippers Movement
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		flipper1->flipper_paddle->SetImpulse(-360);
		flipper3->flipper_paddle->SetImpulse(-360 * 0.8);
	}
	// Right Flippers Movement
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		flipper2->flipper_paddle->SetImpulse(360);
		flipper4->flipper_paddle->SetImpulse(360 * 0.8);
	}
	// Flippers PlayFx
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		App->audio->PlayFx(flipper1->fx);
	}
	// Launcher Movement
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		dynamic_launcher->SetPush(0, 200, 0, 0);
	}
	// Launcher PlayFx
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{
		App->audio->PlayFx(launcher_fx);
	}
	// Apply Force to Ball
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
	{
		ball->ball_body->SetPush(0, -200, 0, 0);
	}

	// Draw all -----------------------------------
	int x, y;
	// Flipers
	flipper1->flipper_paddle->GetPosition(x, y);
	App->renderer->Blit(flipper1->paddle_texture, x, y, NULL, 1.0f, flipper1->flipper_paddle->GetRotation(), 0, 0);

	flipper2->flipper_paddle->GetPosition(x, y);
	App->renderer->Blit(flipper2->paddle_texture, x, y, NULL, 1.0f, flipper2->flipper_paddle->GetRotation(), 0, 0);

	flipper3->flipper_paddle->GetPosition(x, y);
	App->renderer->Blit(flipper3->paddle_texture, x, y, NULL, 1.0f, flipper3->flipper_paddle->GetRotation(), 0, 0);

	flipper4->flipper_paddle->GetPosition(x, y);
	App->renderer->Blit(flipper4->paddle_texture, x, y, NULL, 1.0f, flipper4->flipper_paddle->GetRotation(), 0, 0);

	// Launcher
	dynamic_launcher->GetPosition(x, y);
	App->renderer->Blit(launcher_tex, x - 5, y, NULL);
	
	// Ball
	ball->ball_body->GetPosition(x, y);
	App->renderer->Blit(ball->ball_text, x, y, NULL, 1.0f, ball->ball_body->GetRotation());	
	
	return UPDATE_CONTINUE;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(ball_tex4);
	App->textures->Unload(launcher_tex);
	App->textures->Unload(flipper1->paddle_texture);
	App->textures->Unload(flipper2->paddle_texture);
	App->textures->Unload(flipper3->paddle_texture);
	App->textures->Unload(flipper4->paddle_texture);

	App->physics->DestroyBody(flipper1->flipper_paddle);
	App->physics->DestroyBody(flipper1->flipper_support);
	App->physics->DestroyBody(flipper2->flipper_paddle);
	App->physics->DestroyBody(flipper2->flipper_support);
	App->physics->DestroyBody(flipper3->flipper_paddle);
	App->physics->DestroyBody(flipper3->flipper_support);
	App->physics->DestroyBody(flipper4->flipper_paddle);
	App->physics->DestroyBody(flipper4->flipper_support);

	return true;
}


// Utilities ----------------------------------
// Create Flipper Object
Flipper* ModulePlayer::CreateFlipper(int pos_x, int pos_y, int radius, int* points, int size, int type)
{
	Flipper* flipp = new Flipper();

	flipp->flipper_support = App->physics->CreateCircle(pos_x, pos_y, radius, b_static, 0, false);
	flipp->flipper_paddle = App->physics->CreatePolygon(pos_x, pos_y, points, size, b_dynamic, 0, false);
	flipp->flipper_dir = type;

	flipp->flipper_paddle->body->IsBullet();

	return flipp;
}

// Create Launcher Object
void ModulePlayer::CreateLauncher()
{
	static_launcher = App->physics->CreateCircle(655, 1100, 5, b_static, 0, false);
	dynamic_launcher = App->physics->CreateRectangle(655, 950, 14, 14);

	App->physics->CreatePrismaticJoint(dynamic_launcher->body, static_launcher->body, 0, 1, 0, 0, 0, 0, 0, 75, -50, true, 200, 100);
}

// Create Ball Object
Ball* ModulePlayer::CreateBallz(int pos_x, int pos_y)
{
	Ball* ball = new Ball();

	int x = pos_x;
	int y = pos_y;

	ball->ball_body = App->physics->CreateCircle(x, y, 31 * 0.5f, b_dynamic, 0, false);
	
	ball->ball_text = ball_tex4;

	ball->ball_body->listener = this;

	return ball;
}


