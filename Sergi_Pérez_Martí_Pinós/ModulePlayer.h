#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "ModuleTextures.h"

struct Flipper
{
	PhysBody*		flipper_support;
	PhysBody*		flipper_paddle;
	int				flipper_dir;
	SDL_Texture*	paddle_texture;
	uint			fx;

	Flipper() : paddle_texture(NULL), flipper_support(NULL), flipper_paddle(NULL)
	{}
};

struct Ball
{
	PhysBody*		ball_body;
	SDL_Texture*	ball_text;

	Ball() : ball_text(NULL), ball_body(NULL)
	{}
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	// Utilities
	Flipper* CreateFlipper(int pos_x, int pos_y, int radius, int* points, int size, int type);
	Ball* CreateBallz(int pos_x, int pos_y);
	void CreateLauncher();

public:
	// Flippers
	Flipper*			flipper1;
	Flipper*			flipper2;
	Flipper*			flipper3;
	Flipper*			flipper4;
	// Launcher
	PhysBody*			dynamic_launcher;
	PhysBody*			static_launcher;
	SDL_Texture*		launcher_tex;
	uint				launcher_fx;
	// Ball
	Ball*				ball;
	SDL_Texture*		ball_tex4;
	// Score & Lives
	uint				lose_fx;
	uint				restart_fx;
	uint				last_score = 0;
	uint				score = 0;
	uint				lives = 4;
};