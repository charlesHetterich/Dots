#pragma once
#include "globalVariablesAndIncludes.h"
#include "Input.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Sprite.h"
#include "Entities.h"
#include "Screen.h"

class Game
{
public:
	Game();
	~Game();

	void input(Input input);
	void update();
	void render();

private:

	enum
	{
		HOME_SCREEN,
		GAME_SCREEN,

		NUM_SCREENS
	};

	Screen* screen[NUM_SCREENS];

	//---------------------------------------------------------------------------
	//CORE
	//---------------------------------------------------------------------------
	//shaders
	enum
	{
		BASIC_SHADER,
		PIXEL_SHADER,
		WAVEY_SHADER,

		NUM_SHADERS
	};
	Shader* shader[NUM_SHADERS];

	//textures
	enum
	{
		NO_TEXTURE,
		SPRITE_SHEET,

		NUM_TEXTURES
	};
	CTexture* texture[NUM_TEXTURES];
};

