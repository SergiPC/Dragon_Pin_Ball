#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

#define BUMPER_TIME 300
#define SUMMON_TIME 3600*6

//class PhysBody;

struct Bumper
{
	Bumper() : body(NULL), texture(NULL), hit_timer(0), fx1(0), fx2(0), fx3(0)
	{}

	PhysBody*		body;
	SDL_Texture*	texture;
	Uint32			hit_timer;
	uint			fx1;
	uint			fx2;
	uint			fx3;
};

class ModuleSceneIntro;

struct SensorLight
{
	SensorLight() : body(NULL), on(false), fx(0)
	{}

	SensorLight(ModuleSceneIntro* physics, int x, int y);

	PhysBody*	body;
	bool		on;
	int			x, y;
	uint		fx;
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

	// Utilities
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	void DrawObstacles(p2List<int*> obstacles, p2List<int> lengths);
	void ResetScene();

public:
	p2List<PhysBody*>		obstacles;
	// Background
	PhysBody*				background;
	SDL_Texture*			background_tex;
	// Bumpers
	Bumper					bumper1;
	Bumper					bumper2;
	Bumper					bumper3;
	Bumper					bumper4;
	int						fx;

	Bumper					bumper_left;
	Bumper					bumper_right;;

	// Magic Bean bumper
	Bumper					magic_bean;
	// Kinton bumper
	Bumper					kinton;
	PhysBody*				kinton_support;
	// Mid Savior
	PhysBody*				savior;
	SDL_Texture*			savior_tex;
	// Little Lights
	p2List<SensorLight*>	lights;
	SDL_Texture*			light_tex;
	uint					light_fx;	
	// Dragon Lights
	p2List<SensorLight*>	dragon_balls;
	SDL_Texture*			ball_tex1;
	SDL_Texture*			ball_tex2;
	SDL_Texture*			ball_tex3;
	SDL_Texture*			ball_tex4;
	SDL_Texture*			ball_tex5;
	SDL_Texture*			ball_tex6;
	SDL_Texture*			ball_tex7;
	// Shenron stuff
	bool					all_balls;
	bool					summoned;
	int						summon_timer;
	int						bonus;
	int						shenron_fx;
	SDL_Texture*			shenron_tex;
	SDL_Texture*			x2_tex;
	// Power Pole
	PhysBody*				static_stick;
	PhysBody*				dynamic_stick;
	SDL_Texture*			stick2_tex;

	// Ball must die
	PhysBody*				lose_zone;
	bool					ready_to_move;
};
