#include "Game.h"

int Animation::CANVAS_WIDTH = 2304;
int Animation::CANVAS_HEIGHT = 2304;

int unsigned Screen::CURRENT_SCREEN = 1;

Game::Game()
{
	shader[BASIC_SHADER] = new Shader("basic");
	texture[SPRITE_SHEET] = new CTexture("sprites.png");
	texture[SPRITE_SHEET]->bind(0);
	shader[BASIC_SHADER]->bind();

	screen[HOME_SCREEN] = new HomeScreen(shader[BASIC_SHADER]);
	screen[GAME_SCREEN] = new GameScreen(shader[BASIC_SHADER]);

}

Game::~Game()
{
	delete [] &shader;
	delete [] &texture;
}

void Game::input(Input input)
{
	screen[Screen::CURRENT_SCREEN]->input(input);
}

void Game::update()
{
	screen[Screen::CURRENT_SCREEN]->update();
}

void Game::render()
{
	screen[Screen::CURRENT_SCREEN]->render();
}