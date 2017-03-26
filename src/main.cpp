#include "Game.h"

int main(int argc, char* argv[]){

	Game::Instance().init("Chapter 1", 100, 100, 640, 480, false);

	while(Game::Instance().running()){
		Game::Instance().handleEvents();
		Game::Instance().update();
		Game::Instance().render();

		SDL_Delay(10);
	}

	Game::Instance().clean();

	return 0;
}
