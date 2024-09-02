#include "MainGame.h"

MainGame::~MainGame()
{
}

MainGame::MainGame() : m_window(nullptr), m_width(800), m_height(600), _time(0), gameState(GameState::PLAY)
{
	
}

void MainGame::run()
{
	initSystems();

	_sprite.init(-1, -1, 2, 2);

	_texture = ImageLoader::loadPNG("Textures/PNG/bush.png");

	gameLoop();
}

void MainGame::initSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	m_window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_OPENGL);
	if(!m_window)
		fatalError("Window couldn't be created");

	SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
	if(!glContext)
		fatalError("SDL_GL_CONTEXT couldn't be created");

	glewExperimental = true;
	GLenum status = glewInit();
	if(status != GLEW_OK)
		fatalError("Couldn't initialize glew");

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(1,0,1,0);

	initShaders();
}

void MainGame::initShaders()
{
	_program.compileShaders("Shaders/default.vert", "Shaders/default.frag");
	_program.bindAttribute("vertexPos");
	_program.bindAttribute("vertexColor");
	_program.bindAttribute("UV");
	_program.linkShaders();
}

void MainGame::gameLoop()
{
	while (gameState != GameState::EXIT)
	{
		_time += 0.01;
		processInput();
		drawGame();
	}
}

void MainGame::drawGame()
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_program.use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture.ID);
	GLint textureLocation = _program.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);


	_sprite.draw();
	GLuint timeLocation = _program.getUniformLocation("time");
	glUniform1f(timeLocation, _time);

	glBindTexture(GL_TEXTURE_2D, 0);
	_program.unuse();

	SDL_GL_SwapWindow(m_window);
}

void MainGame::processInput()
{
	SDL_Event evnt; 
	while(SDL_PollEvent(&evnt))
	{
		switch(evnt.type)
		{
			case SDL_QUIT:
				gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				
				break;
		}
	}
}
