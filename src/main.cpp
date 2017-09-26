/*Copyright 2017 MIT*/

#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* argv[]) {
    Uint32 frameStart, frameTime;

    const int center = engine::Game::Instance().getCenterScreen();
    engine::Game::Instance().init("RGBender", center, center,
                          1366, 768, false);

    while (engine::Game::Instance().running()) {
        frameStart = SDL_GetTicks();
        engine::Game::Instance().handleEvents();
        engine::Game::Instance().update();
        engine::Game::Instance().render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < DELAY_TIME) {
            SDL_Delay(static_cast<int>(DELAY_TIME - frameTime));
        }
    }

    engine::Game::Instance().clean();

    return 0;
}
