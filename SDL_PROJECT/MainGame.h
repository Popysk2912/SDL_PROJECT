#pragma once
#include "errors.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "glslProgram.h"
#include "Sprite.h"
#include "GLTexture.h"

#include "ImageLoader.h"

#define uint unsigned int

enum class GameState 
{
	PLAY,
	EXIT
};


class MainGame
{
public:
	~MainGame();
	MainGame();

	void run();

	
private:
	SDL_Window* m_window;
	uint m_width;
	uint m_height;

	GameState gameState;

	Sprite _sprite;
	GLSLProgram _program;
	GLTexture _texture;

	float _time;

	void initSystems();
	void initShaders();
	void gameLoop();
	void drawGame();
	void processInput();
};

