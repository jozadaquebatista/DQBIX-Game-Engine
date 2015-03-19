#include "..\include\TestGame.h"


TestGame::TestGame()
{
	img = new image("data/monkey_d.png");
}

TestGame::~TestGame()
{
}

void TestGame::input()
{
	if (Input::getKeyDown(SDLK_a))
		printf("A was pressed\n");
}

void TestGame::update()
{

}

void TestGame::render()
{
	
}
