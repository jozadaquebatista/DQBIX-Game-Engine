#include "..\include\TestGame.h"


TestGame::TestGame()
{
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
