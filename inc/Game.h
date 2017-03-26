#ifndef GAME_H
#define GAME_H

#include "TextureManager.h"
#include "GameObject.h"

#include <SDL2/SDL.h>
#include <vector>

class Game{
public:
	
	static Game& Instance(){
		static Game game;

		return game;
	}

	Game(Game const&) = delete;
	void operator=(Game const&) = delete;

	// simply set the running variable to true
	bool init(const char*, int, int, int, int, bool);

	void render();
	void update();
	void handleEvents();
	void clean();
	void draw();

	SDL_Renderer* getRenderer(){
		return m_pRenderer;
	}

	// a function to access the private running variable
	bool running() { return m_bRunning; }

private:
	Game() {}

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	GameObject* m_go;
	GameObject* m_player;
	GameObject* m_enemy;

	std::vector<GameObject*> m_gameObjects;

	int m_currentFrame;
	bool m_bRunning;
};

#endif
