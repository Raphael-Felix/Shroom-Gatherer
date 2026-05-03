#include <SFML/Graphics.hpp>
#include <iostream>

#include "GameManager.h"
#include "GameScene.h"

#include <cstdlib>
#include <crtdbg.h>

int main()
{
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	srand(time(NULL));

	GameManager::Get()->CreateWindow(1680, 760, "Gather mushrooms", 120, sf::Color(0, 48, 59));

	GameManager::Get()->LaunchScene<GameScene>();

	return 0;
}
