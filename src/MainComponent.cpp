#include "..\include\MainComponent.h"

float MainComponent::FRAME_CAP = 60.0f;

MainComponent::MainComponent(Game* game)
{
	running = false;
	if (game == nullptr)
	{
		printf("You can't simply pass a NULL game... \n");
		exit(EXIT_FAILURE);
	}
	else
		m_game = game;
}


MainComponent::~MainComponent()
{

}

void MainComponent::start()
{
	if (running) return;
	run();
}
void MainComponent::stop()
{
	if (!running) return;
	running = false;
}
void MainComponent::run()
{
	running = true;

	const float frameTime = 1.0f / (float)FRAME_CAP;

	int lastTime = Time::getTime();
	float unprocessedTime = 0.0f;

	int frames = 0;
	int frameCounter = 0;

	while (running)
	{
		bool can_render = false;

		int startTime = Time::getTime();
		int passedTime = startTime - lastTime;
		lastTime = startTime;
		
		unprocessedTime += (float)passedTime / (float)Time::SECOND;
		frameCounter += passedTime;

		while (unprocessedTime > frameTime)
		{
			can_render = true;

			unprocessedTime -= frameTime;

			Time::setDelta(frameTime);
			Input::update();

			if (Window::closed())
				stop();

			m_game->input();
			m_game->update();

			if (frameCounter >= Time::SECOND)
			{
				printf("FPS: %d\n", frames);
				frames = 0;
				frameCounter = 0;
			}
		}
		if (can_render)
		{
			render();
			frames++;
		}
		else
			SDL_Delay(1);
	}
	clean();
	SDL_Quit();
}
void MainComponent::render()
{
	m_game->render();
	Window::render();
}
void MainComponent::clean()
{

}