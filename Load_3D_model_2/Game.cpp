#include "Game.h"
#include "InputHandler.h"
#include "GL\glew.h"
#include "GL\freeglut.h"
#include "IL\il.h"
#include "IL\ilu.h"
#include "IL\ilut.h"
#include "SDL\SDL_mixer.h"

#include <iostream>
#include <assert.h>

Game::Game()
{
	std::cout << "konstructor Game()" << std::endl;

	screen_width = 1024;
	screen_height = 768;

	running = true;
}


Game::~Game()
{

}

void Game::init()
{
	assert(2 < 5);

	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		// SET ATTRIBUTE ONLY after initialize
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); // on antialiasing sdl
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); //subsamples for each pixel

		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1); // set to 1 to require hardware acceleration

		SDL_DisplayMode dm;
		SDL_GetDesktopDisplayMode(0, &dm); // if resolution change in SDL, this function will return the previous native display mode !!!
		screen_width = dm.w;
		screen_height = dm.h;
		std::cout << dm.w << "    " << dm.h << std::endl;

		window = SDL_CreateWindow("Chapter 1",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			screen_width, screen_height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | 0);

		//SDL_SetWindowOpacity(window, 0.0f); // make window transparent ( prozra4noe )

		if (window != 0)
		{
			glcontext = SDL_GL_CreateContext(window);
			std::cout << "SDL init " << std::endl;
		}
	}
	else
	{
		std::cout << "window create error " << std::endl;
		return; // sdl could not initialize
	}
	SDL_SetWindowFullscreen(window, 0); // ����������� ������� / ������������� ����� � ������� ��� ������ ��������� GL 

	glewExperimental = GL_TRUE; //��� ���������� � ��������������� ������� ����� ����� ����������.
	if (glewInit())// if all is init return 0 !! if not init return 1 and if() run
	{
		std::cout << "glew init error !" << std::endl;
	}

	ilInit(); // init image load library
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
	ilEnable(IL_ORIGIN_SET); 
	// OpenGL have the 0.0 coordinate on the bottom y-axis, but images usually have 0.0 at the top of the y-axis.
	ilOriginFunc(IL_ORIGIN_UPPER_LEFT); // 0, 0 textures in upper left side

										// MIX_DEFAULT_FREQUENCY = sample rate = frequensy = speed playing
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4069) == -1)
		cout << "Mixer NOT init !!" << endl;
	Mix_VolumeMusic(1);

	glViewport(0, 0, screen_width, screen_height); // ������ ������������� ����
	glEnable(GL_DEPTH_TEST); // �������� ���� �������

	//glMatrixMode(GL_PROJECTION); ����� ������� �������.( GL_MODELVIEW- ��������� � ���������� �����(�� ���������))
	//glLoadIdentity(); // replace the current matrix(modelview ) with the user matrix (GL_PROJECTION)
	//glOrtho(0.0, 920.0, 900.0, 0.0, -1.0, 1.0);  - ���� 2� ����� ����������
	//glMatrixMode(GL_MODELVIEW);

	int buffer;
	SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &buffer);
	printf("SDL_GL_DOUBLEBUFFER: %d \n", buffer);

	triangle.init();

}

void Game::handleEvents()
{
	InputHandler::Instance()->updateEvent();
}

void Game::update()
{
	triangle.update();
}

void Game::render()
{
	// �������� ��� ��������� �������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	triangle.render();


	glFlush(); // ����������� �������, ��������� ���������� ������ // �� ���� ����������
	//glFinish(); //���� ���� ��� ���������� ������� �� ����� ����������
	SDL_GL_SwapWindow(window);//���������� ������ ��� ������������ ���� �� ������.
	 
}

void Game::playSound()
{
	triangle.playSound();
}

void Game::clean()
{
	std::cout << "cleaning " << std::endl;
	running = false;
	SDL_DestroyWindow(window);
	SDL_Quit();

}