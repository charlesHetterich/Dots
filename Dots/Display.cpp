#include "Display.h"

CDisplay::CDisplay(int w, int h, const std::string& title)
{
	isClosed = false;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);
	glContext = SDL_GL_CreateContext(window);
	
	glewExperimental = GL_TRUE;
	GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		std::cerr << "Glew failed to initialize" << std::endl;
		isClosed = true;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glEnable(GL_STENCIL_TEST);
	//glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	//glDepthMask(GL_FALSE);
	//glStencilFunc(GL_EQUAL, 1, 0xFF);
	//glStencilMask(0x00);
	
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	int W;
	int H;
	SDL_GetWindowSize(window, &W, &H);
	std::cout << "width: " << W << std::endl;
	std::cout << "height: " << H << std::endl;

	SCREEN_RATIO = (float)W / (float)H;
	SCREEN_WIDTH = (float)W;
	SCREEN_HEIGHT = (float)H;
}
CDisplay::~CDisplay()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void CDisplay::clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CDisplay::updateWindow()
{
	SDL_GL_SwapWindow(window);

	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			isClosed = true;
	}
}

bool CDisplay::getClosed()
{
	return isClosed;
}