#include "stdafx.h"
#include "Game/Game.h"

int main() {
	auto game = Game::getInstance();
	game->init()->run()->Dispose();
	return 0;
}