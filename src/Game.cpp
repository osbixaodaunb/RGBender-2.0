#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "LoaderParams.h"
#include "InputHandler.h"

#include <iostream>
#include <vector>
#include <SDL2/SDL_image.h>

using namespace std;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
	int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

	// attempt to initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) >= 0){
		cout << "SDL init success" << endl;
			
		// init the window
		m_pWindow = SDL_CreateWindow(title, 
									 xpos, ypos, 
									 width, height, 
									 flags);
		
		if(m_pWindow != 0){
			// window init success
			cout << "Window creation success" << endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if(m_pRenderer != 0){
				// renderer init success
				cout << "Renderer creation success" << endl;
				SDL_SetRenderDrawColor(m_pRenderer,
										 255, 255, 255, 255);
			} else {
				// renderer init failed
				cout << "Renderer init failed" << endl;
					return false;
			}
		} else {
			// window init failed
			cout << "Window init failed" << endl;
			return false;
		}
	} else {
		// SDL init failed
		cout << "SDL init failed" << endl;
		return false;
	}

	InputHandler::Instance().initialiseJoysticks();

	cout << "Init success" << endl;
	
	m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "cat")));
	m_gameObjects.push_back(new Enemy(new LoaderParams(300, 300, 128, 82, "cat")));

	TheTextureManager::Instance().load("assets/anim.png", "cat", m_pRenderer);
	
	// everything inited successfully, start the main loop
	m_bRunning = true;

	return true;
}

void Game::draw(){
	for(GameObject* gameObject : m_gameObjects){
		gameObject->draw();
	}
}

void Game::render(){
	// clear the renderer to the draw color
	SDL_RenderClear(m_pRenderer);

	draw();

	// draw to screen
	SDL_RenderPresent(m_pRenderer);
}

void Game::update(){
	m_currentFrame = int(SDL_GetTicks()/100 % 6);

	for(GameObject* gameObject : m_gameObjects){
		gameObject->update();
	}

}

void Game::handleEvents(){
	InputHandler::Instance().update();
}

void Game::clean(){
	cout << "Cleaning game" << endl;

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);

	InputHandler::Instance().clean();

	IMG_Quit();
	SDL_Quit();
}

void Game::quit(){
	m_bRunning = false;
}
