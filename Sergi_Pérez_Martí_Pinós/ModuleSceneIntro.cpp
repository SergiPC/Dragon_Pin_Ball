#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	background_tex = NULL;
	all_balls = false;
	summoned = false;
	ready_to_move = false;
	bonus = 1;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	// Background Music
	App->audio->PlayMusic("pinball/Dragon_Pin_Ball_Fx/DB - Music_-10.wav", 0.0f);

	// Load Textures ------------------------------
	background_tex = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Background.png");

	stick2_tex = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Power_Pole_02.png");
	kinton.texture = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Bumper_Kinton01.png");
	savior_tex = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Helper_Purple.png");
	light_tex = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Sensor_Lights_On.png");
	shenron_tex = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Shenron_02.png");
	x2_tex = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_x2.png");

	ball_tex1 = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Balls_Dragon_Ball_01.png");
	ball_tex2 = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Balls_Dragon_Ball_02.png");
	ball_tex3 = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Balls_Dragon_Ball_03.png");
	ball_tex4 = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Balls_Dragon_Ball_04.png");
	ball_tex5 = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Balls_Dragon_Ball_05.png");
	ball_tex6 = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Balls_Dragon_Ball_06.png");
	ball_tex7 = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Balls_Dragon_Ball_07.png");

	bumper1.texture = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Bumper_Buu_Hit.png");
	bumper2.texture = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Bumper_Freezer_Hit.png");
	bumper3.texture = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Bumper_Babidi_Hit.png");
	bumper4.texture = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_Bumper_Cell_Hit.png");
	bumper_left.texture = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_explosion01.png");
	bumper_right.texture = App->textures->Load("pinball/Dragon_Pin_Ball/DPB_explosion02.png");

	// Load Music Fx ------------------------------
	bumper1.fx1 = bumper2.fx1 = bumper3.fx1 = bumper4.fx1 = App->audio->LoadFx("pinball/Dragon_Pin_Ball_Fx/DB - Punch Medium02_-20.wav");
	bumper1.fx2 = bumper2.fx2 = bumper3.fx2 = bumper4.fx2 = App->audio->LoadFx("pinball/Dragon_Pin_Ball_Fx/DB - Combo01_-20.wav");
	bumper1.fx3 = bumper2.fx3 = bumper3.fx3 = bumper4.fx3 = App->audio->LoadFx("pinball/Dragon_Pin_Ball_Fx/DB - Combo03_-20.wav");
	bumper_left.fx1 = bumper_right.fx1 = App->audio->LoadFx("pinball/Dragon_Pin_Ball_Fx/DB - Punch Regular_-20.wav");
	kinton.fx1 = App->audio->LoadFx("pinball/Dragon_Pin_Ball_Fx/DB - Kinton.wav");
	light_fx = magic_bean.fx1 = App->audio->LoadFx("pinball/Dragon_Pin_Ball_Fx/DB - Teleport_-20.wav");
	shenron_fx = App->audio->LoadFx("pinball/Dragon_Pin_Ball_Fx/DB - Shenron eyes Glowing_-15.wav");

	// Fx Counter for Bumpers
	fx = 1;

	// Chains Points ------------------------------
	// Background
	int bground[74] = {
		575, 80,
		643, 141,
		666, 201,
		666, 1139,
		643, 1139,
		643, 1019,
		628, 1007,
		628, 562,
		594, 589,
		527, 744,
		568, 771,
		618, 771,
		618, 1002,
		389, 1133,
		388, 1143,
		701, 1143,
		701, 1,
		1, 1,
		0, 1143,
		261, 1143,
		260, 1134,
		33, 1006,
		33, 772,
		80, 771,
		120, 744,
		38, 553,
		47, 519,
		77, 525,
		100, 581,
		103, 558,
		47, 443,
		28, 428,
		28, 211,
		52, 128,
		94, 84,
		176, 49,
		500, 50
	};

	// Bouncers
	int bouncer_1[8] = {
		140, 802,
		138, 808,
		193, 935,
		201, 930
	};

	int bouncer_2[8] = {
		505, 802,
		509, 808,
		453, 935,
		444, 930
	};

	// Background Obstacles
	int obstacle1[10] = {
		138, 799,
		118, 805,
		120, 914,
		187, 951,
		200, 943
	};

	int obstacle2[10] = {
		507, 798,
		525, 807,
		524, 914,
		458, 952,
		445, 943
	};
	
	int obstacle3[36] = {
		255, 86,
		191, 86,
		137, 107,
		89, 154,
		76, 194,
		76, 308,
		92, 318,
		121, 293,
		122, 158,
		103, 145,
		143, 107,
		143, 146,
		137, 156,
		137, 290,
		146, 294,
		153, 289,
		154, 166,
		254, 120
	};

	int obstacle4[28] = {
		437, 86,
		503, 90,
		557, 112,
		603, 160,
		617, 193,
		620, 363,
		565, 488,
		550, 488,
		605, 371,
		604, 195,
		591, 160,
		548, 115,
		498, 96,
		437, 96
	};

	int obstacle4_1[22] = {
		459, 130,
		490, 132,
		533, 154,
		550, 219,
		555, 283,
		554, 372,
		538, 372,
		483, 267,
		485, 241,
		469, 213,
		451, 150
	};

	int obstacle5[14] = {
		72, 813,
		72, 938,
		82, 953,
		175, 1007,
		178, 997,
		81, 942,
		81, 812
	};

	int obstacle6[14] = {
		464, 999,
		564, 943,
		564, 814,
		573, 814,
		573, 939,
		565, 953,
		470, 1005
	};

	int obstacle7[8] = {
		314, 95,
		322, 100,
		315, 118,
		307, 100
	};

	int obstacle8[8] = {
		384, 95,
		392, 100,
		385, 118,
		377, 100
	};

	p2List<int*> tmp_obstacles;
	p2List<int> tmp_length;

	tmp_obstacles.add(obstacle1);
	tmp_obstacles.add(obstacle2);
	tmp_obstacles.add(obstacle3);
	tmp_obstacles.add(obstacle4);
	tmp_obstacles.add(obstacle4_1);
	tmp_obstacles.add(obstacle5);
	tmp_obstacles.add(obstacle6);
	tmp_obstacles.add(obstacle7);
	tmp_obstacles.add(obstacle8);

	// Bumpers
	bumper1.body = App->physics->CreateCircle(257, 220, 20, b_static, 1, false);
	bumper1.body->listener = this;
	bumper2.body = App->physics->CreateCircle(327, 270, 20, b_static, 1, false);
	bumper2.body->listener = this;
	bumper3.body = App->physics->CreateCircle(327, 170, 20, b_static, 1.5, false);
	bumper3.body->listener = this;
	bumper4.body = App->physics->CreateCircle(397, 220, 20, b_static, 1, false);
	bumper4.body->listener = this;

	// Triangle Bumpers
	bumper_left.body = App->physics->CreatePolygon(0, 0, bouncer_1, 8, b_static, 1.2, false);
	bumper_left.body->listener = this;
	bumper_right.body = App->physics->CreatePolygon(0, 0, bouncer_2, 8, b_static, 1.2, false);
	bumper_right.body->listener = this;

	// Magic Bean
	magic_bean.body = App->physics->CreateCircle(125, 145, 5, b_static, 0, false);
	magic_bean.body->listener = this;

	// Scene
	background = App->physics->CreateStaticChain(0, 0, bground, 74);

	obstacles.add(App->physics->CreateStaticChain(0, 0, obstacle1, 10));
	obstacles.add(App->physics->CreateStaticChain(0, 0, obstacle2, 10));
	obstacles.add(App->physics->CreateStaticChain(0, 0, obstacle3, 36));
	obstacles.add(App->physics->CreateStaticChain(0, 0, obstacle4, 28));
	obstacles.add(App->physics->CreateStaticChain(0, 0, obstacle4_1, 22));
	obstacles.add(App->physics->CreateStaticChain(0, 0, obstacle5, 14));
	obstacles.add(App->physics->CreateStaticChain(0, 0, obstacle6, 14));
	obstacles.add(App->physics->CreateStaticChain(0, 0, obstacle7, 8));
	obstacles.add(App->physics->CreateStaticChain(0, 0, obstacle8, 8));

	// Kinton
	int obs_kinton[8] = {
		0, 30,
		40, 0,
		80, 30,
		40, 60
	};

	kinton.body = App->physics->CreatePolygon(330, 700, obs_kinton, 8, b_dynamic, 0.75, false);
	kinton.body->listener = this;
	kinton_support = App->physics->CreateCircle(5, 700, 2, b_static, 0, false);

	App->physics->CreatePrismaticJoint(kinton_support->body, kinton.body->body, 1, 0, 0, 0, 0, 0, 0, 500, -500, false, 0, 0);

	// Power Pole
	static_stick = App->physics->CreateCircle(129, 242, 5, b_static, 0, false);
	dynamic_stick = App->physics->CreateRectangle(129, 218, 7, 86);

	App->physics->CreatePrismaticJoint(static_stick->body, dynamic_stick->body, 0, 1, 0, 0, 0, 0, 0, 15, -60, true, 1, 1);

	// Mid Savior
	savior = App->physics->CreateCircle(325, 1110, 10, b_static, 0.75, false);

	// Lights
	SensorLight* tmp;

	lights.add(tmp = new SensorLight(this, 175, 184));
	lights.add(tmp = new SensorLight(this, 53, 394));
	lights.add(tmp = new SensorLight(this, 53, 334));
	lights.add(tmp = new SensorLight(this, 52, 272));
	lights.add(tmp = new SensorLight(this, 53, 211));
	lights.add(tmp = new SensorLight(this, 70, 148));
	lights.add(tmp = new SensorLight(this, 114, 99));

	lights.add(tmp = new SensorLight(this, 180, 72));
	lights.add(tmp = new SensorLight(this, 281, 110));
	lights.add(tmp = new SensorLight(this, 349, 110));

	lights.add(tmp = new SensorLight(this, 415, 110));
	lights.add(tmp = new SensorLight(this, 494, 70));
	lights.add(tmp = new SensorLight(this, 563, 94));
	lights.add(tmp = new SensorLight(this, 641, 222));
	lights.add(tmp = new SensorLight(this, 641, 284));
	lights.add(tmp = new SensorLight(this, 641, 351));
	lights.add(tmp = new SensorLight(this, 639, 414));

	lights.add(tmp = new SensorLight(this, 486, 112));
	lights.add(tmp = new SensorLight(this, 580, 317));
	lights.add(tmp = new SensorLight(this, 580, 369));
	lights.add(tmp = new SensorLight(this, 560, 417));
	lights.add(tmp = new SensorLight(this, 541, 462));

	lights.add(tmp = new SensorLight(this, 83, 599));
	lights.add(tmp = new SensorLight(this, 98, 641));

	lights.add(tmp = new SensorLight(this, 112, 780));
	lights.add(tmp = new SensorLight(this, 106, 930));
	lights.add(tmp = new SensorLight(this, 532, 780));
	lights.add(tmp = new SensorLight(this, 544, 929));

	// Dragon Ballz
	dragon_balls.add(tmp = new SensorLight(this, 298, 451));
	dragon_balls.add(tmp = new SensorLight(this, 357, 450));
	dragon_balls.add(tmp = new SensorLight(this, 386, 503));
	dragon_balls.add(tmp = new SensorLight(this, 359, 556));
	dragon_balls.add(tmp = new SensorLight(this, 299, 555));
	dragon_balls.add(tmp = new SensorLight(this, 266, 504));
	dragon_balls.add(tmp = new SensorLight(this, 328, 504));

	// Lose-zone - Sensor for player losing
	int lose_zone_points[8]
	{
		0, 1200,
		700, 1200,
		700, 1250,
		0, 1250
	};

	lose_zone = App->physics->CreatePolygon(0, 0, lose_zone_points, 8, b_static, 0, false);
	lose_zone->listener = this;

	return ret;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	// Set ball position
	if (ready_to_move)
	{
		App->player->ball->ball_body->SetPosition(650, 700);
		ready_to_move = false;
	}

	// Draw all -----------------------------------
	App->renderer->Blit(background_tex, 0, 0);

	int x, y;
	// Power Pole
	dynamic_stick->GetPosition(x, y);
	App->renderer->Blit(stick2_tex, x, y);

	// Kinton
	kinton.body->GetPosition(x, y);
	App->renderer->Blit(kinton.texture, x - 10, y);

	// Mid Savior
	savior->GetPosition(x, y);
	App->renderer->Blit(savior_tex, x, y);

	// Turn on lights
	p2List_item<SensorLight*>* tmp_sensor = lights.getFirst();

	while (tmp_sensor != NULL)
	{
		if (tmp_sensor->data->on == true)
			App->renderer->Blit(light_tex, tmp_sensor->data->x - 10, tmp_sensor->data->y - 10);

		tmp_sensor = tmp_sensor->next;
	}

	// Turn off lights
	tmp_sensor = lights.getFirst();
	
	while (tmp_sensor != NULL)
	{
		if (tmp_sensor->data->on == false)
			break;

		if (tmp_sensor == lights.getLast())
		{
			tmp_sensor = lights.getFirst();

			while (tmp_sensor != NULL)
			{
				tmp_sensor->data->on = false;
				tmp_sensor = tmp_sensor->next;
			}
			break;
		}
		tmp_sensor = tmp_sensor->next;
	}

	// Turn on dragon ballz
	tmp_sensor = dragon_balls.getFirst();
	int i = 1;

	while (tmp_sensor != NULL)
	{
		if (tmp_sensor->data->on == true)
		{
			if (i == 1)
			{
				App->renderer->Blit(ball_tex1, tmp_sensor->data->x - 15, tmp_sensor->data->y - 15);
			}
			if (i == 2)
			{
				App->renderer->Blit(ball_tex2, tmp_sensor->data->x - 15, tmp_sensor->data->y - 15);
			}
			if (i == 3)
			{
				App->renderer->Blit(ball_tex3, tmp_sensor->data->x - 15, tmp_sensor->data->y - 15);
			}
			if (i == 4)
			{
				App->renderer->Blit(ball_tex4, tmp_sensor->data->x - 15, tmp_sensor->data->y - 15);
			}
			if (i == 5)
			{
				App->renderer->Blit(ball_tex5, tmp_sensor->data->x - 15, tmp_sensor->data->y - 15);
			}
			if (i == 6)
			{
				App->renderer->Blit(ball_tex6, tmp_sensor->data->x - 15, tmp_sensor->data->y - 15);
			}
			if (i == 7)
			{
				App->renderer->Blit(ball_tex7, tmp_sensor->data->x - 15, tmp_sensor->data->y - 15);
			}
		}
		i++;
		tmp_sensor = tmp_sensor->next;
	}

	// Turn off dragon ballz
	tmp_sensor = dragon_balls.getFirst();

	while (tmp_sensor != NULL)
	{
		if (tmp_sensor->data->on == false)
			break;

		if (tmp_sensor == dragon_balls.getLast())
		{
			if (all_balls == false && summoned == false)
			{
				summon_timer = SDL_GetTicks() + SUMMON_TIME;
				App->audio->PlayFx(shenron_fx);
				bonus = 2;
			}
			all_balls = true;
			summoned = true;

			if (SDL_TICKS_PASSED(SDL_GetTicks(), summon_timer) == true && summoned)
			{
				all_balls = false;
				summoned = false;
				App->audio->PlayFx(shenron_fx);
				bonus = 1;
				tmp_sensor = dragon_balls.getFirst();
				
				while (tmp_sensor != NULL)
				{
					tmp_sensor->data->on = false;
					tmp_sensor = tmp_sensor->next;
				}
			}
			break;
		}
		tmp_sensor = tmp_sensor->next;
	}

	// Shenron & bonus
	if (summoned)
	{
		App->renderer->Blit(shenron_tex, 223, 374);
		App->renderer->Blit(x2_tex, 248, 710);
	}

	return UPDATE_CONTINUE;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	lights.clear();
	dragon_balls.clear();

	App->textures->Unload(background_tex);
	App->textures->Unload(stick2_tex);
	App->textures->Unload(bumper1.texture);
	App->textures->Unload(bumper2.texture);
	App->textures->Unload(bumper3.texture);
	App->textures->Unload(bumper4.texture);
	App->textures->Unload(bumper_left.texture);
	App->textures->Unload(bumper_right.texture);
	App->textures->Unload(kinton.texture);
	App->textures->Unload(savior_tex);
	App->textures->Unload(light_tex);

	App->textures->Unload(ball_tex1);
	App->textures->Unload(ball_tex2);
	App->textures->Unload(ball_tex3);
	App->textures->Unload(ball_tex4);
	App->textures->Unload(ball_tex5);
	App->textures->Unload(ball_tex6);
	App->textures->Unload(ball_tex7);

	return true;
}

// Utilities ----------------------------------
void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	// Detects if player lost
	if (lose_zone == bodyA)
	{
		ready_to_move = true;
		App->player->lives--;

		if (App->player->lives <= 0)
		{
			App->player->last_score = App->player->score;
			App->player->score = 0;
			App->player->lives = 4;
			App->audio->PlayFx(App->player->restart_fx);
			ResetScene();
		}
		else
			App->audio->PlayFx(App->player->lose_fx);

		return;
	}

	// Detects bean collision
	if (magic_bean.body == bodyA)
	{
		magic_bean.hit_timer = SDL_GetTicks() + BUMPER_TIME;
		App->player->score += (1500 * bonus);
		App->audio->PlayFx(magic_bean.fx1);
		return;
	}

	// Detects bumpers collision
	if (bumper1.body == bodyA)
	{
		App->player->score += (50 * bonus);
		if (fx == 1)
		{
			bumper1.hit_timer = SDL_GetTicks() + BUMPER_TIME;
			App->audio->PlayFx(bumper1.fx1);
			fx = 2;
			return;
		}
		if (fx == 2)
		{
			bumper1.hit_timer = SDL_GetTicks() + BUMPER_TIME;
			App->audio->PlayFx(bumper1.fx2);
			fx = 3;
			return;
		}
		if (fx == 3)
		{
			bumper1.hit_timer = SDL_GetTicks() + BUMPER_TIME;
			App->audio->PlayFx(bumper1.fx3);
			fx = 1;
			return;
		}
	}

	if (bumper2.body == bodyA)
	{
		App->player->score += (50 * bonus);
		if (fx == 1)
		{
			bumper2.hit_timer = SDL_GetTicks() + BUMPER_TIME;
			App->audio->PlayFx(bumper2.fx1);
			fx = 2;
			return;
		}
		if (fx == 2)
		{
			bumper2.hit_timer = SDL_GetTicks() + BUMPER_TIME;
			App->audio->PlayFx(bumper2.fx2);
			fx = 3;
			return;
		}
		if (fx == 3)
		{
			bumper2.hit_timer = SDL_GetTicks() + BUMPER_TIME;
			App->audio->PlayFx(bumper2.fx3);
			fx = 1;
			return;
		}
	}

	if (bumper3.body == bodyA)
	{
		App->player->score += (50 * bonus);
		if (fx == 1)
		{
			bumper3.hit_timer = SDL_GetTicks() + BUMPER_TIME;
			App->audio->PlayFx(bumper3.fx1);
			fx = 2;
			return;
		}
		if (fx == 2)
		{
			bumper3.hit_timer = SDL_GetTicks() + BUMPER_TIME;
			App->audio->PlayFx(bumper3.fx2);
			fx = 3;
			return;
		}
		if (fx == 3)
		{
			bumper3.hit_timer = SDL_GetTicks() + BUMPER_TIME;
			App->audio->PlayFx(bumper3.fx3);
			fx = 1;
			return;
		}
	}

	if (bumper4.body == bodyA)
	{
		App->player->score += (50 * bonus);
		if (fx == 1)
		{
			bumper4.hit_timer = SDL_GetTicks() + BUMPER_TIME;
			App->audio->PlayFx(bumper4.fx1);
			fx = 2;
			return;
		}
		if (fx == 2)
		{
			bumper4.hit_timer = SDL_GetTicks() + BUMPER_TIME;
			App->audio->PlayFx(bumper4.fx2);
			fx = 3;
			return;
		}
		if (fx == 3)
		{
			bumper4.hit_timer = SDL_GetTicks() + BUMPER_TIME;
			App->audio->PlayFx(bumper4.fx3);
			fx = 1;
			return;
		}
	}

	if (bumper_left.body == bodyA)
	{
		App->player->score += (50 * bonus);
		bumper_left.hit_timer = SDL_GetTicks() + BUMPER_TIME;
		App->audio->PlayFx(bumper_left.fx1);
		return;
	}

	if (bumper_right.body == bodyA)
	{
		App->player->score += (50 * bonus);
		bumper_right.hit_timer = SDL_GetTicks() + BUMPER_TIME;
		App->audio->PlayFx(bumper_right.fx1);
		return;
	}

	// Detects kinton collision
	if (kinton.body == bodyA && App->player->ball->ball_body == bodyB)
	{
		App->player->score += (150 * bonus);
		App->audio->PlayFx(kinton.fx1);
		return;
	}

	// Detects lights collision
	p2List_item<SensorLight*>* tmp_sensor = lights.getFirst();

	while (tmp_sensor != NULL)
	{
		if (bodyA == tmp_sensor->data->body)
		{
			if (tmp_sensor->data->on == false)
			{
				tmp_sensor->data->on = true;
				App->audio->PlayFx(tmp_sensor->data->fx);
				App->player->score += (100 * bonus);
			}
			return;
		}
		tmp_sensor = tmp_sensor->next;
	}

	// Detects dragon ballz collision
	tmp_sensor = dragon_balls.getFirst();

	while (tmp_sensor != NULL)
	{
		if (bodyA == tmp_sensor->data->body)
		{
			if (tmp_sensor->data->on == false)
			{
				tmp_sensor->data->on = true;
				App->audio->PlayFx(tmp_sensor->data->fx);
				App->player->score += (1000 * bonus);
			}
			return;
		}
		tmp_sensor = tmp_sensor->next;
	}
}

// Display Borders
void ModuleSceneIntro::DrawObstacles(p2List<int*> tmp_obstacles, p2List<int> tmp_lengths)
{
	p2List_item<int*>* tmp = tmp_obstacles.getFirst();
	p2List_item<int>* tmp2 = tmp_lengths.getFirst();

	while (tmp != NULL)
	{
		obstacles.add(App->physics->CreateStaticChain(0, 0, tmp->data, tmp2->data));

		tmp = tmp->next;
		tmp2 = tmp2->next;
	}
}

void ModuleSceneIntro::ResetScene()
{
	// Turn on lights
	p2List_item<SensorLight*>* tmp_sensor = lights.getFirst();

	while (tmp_sensor != NULL)
	{
		tmp_sensor->data->on = false;
		tmp_sensor = tmp_sensor->next;
	}

	tmp_sensor = dragon_balls.getFirst();

	while (tmp_sensor != NULL)
	{
		tmp_sensor->data->on = false;
		tmp_sensor = tmp_sensor->next;
	}

	summon_timer = 0;
	summoned = false;
	all_balls = false;
	bonus = 1;
}

// SensorLights Constructor
SensorLight::SensorLight(ModuleSceneIntro* scene, int x, int y)
{
	this->x = x;
	this->y = y;

	int radius = 10;
	fx = scene->light_fx;

	body = scene->App->physics->CreateCircle(x, y, radius, b_static, 0, true);
	body->listener = scene;
	on = false;
}