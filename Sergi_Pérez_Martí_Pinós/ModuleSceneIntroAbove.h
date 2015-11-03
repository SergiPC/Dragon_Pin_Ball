#pragma once
#include "Module.h"

class ModuleSceneIntroAbove : public Module
{
public:
	ModuleSceneIntroAbove(Application* app, bool start_enabled = true);
	~ModuleSceneIntroAbove();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture*  Freezer;
	SDL_Texture*  Babidi;
	SDL_Texture*  Cell;
	SDL_Texture*  Buu;
	SDL_Texture*  kame_house_top;
	SDL_Texture*  ship_top;
	SDL_Texture*  bean_tex;
};