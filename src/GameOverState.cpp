#include "GameOverState.h"
#include "GameState.h"
#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"
#include "MenuState.h"
#include "PlayState.h"

#include <iostream>

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update(){
	GameState::update();
}

void GameOverState::render(){
	GameState::render();
}

void GameOverState::s_gameOverToMain(){
	Game::Instance().getStateMachine()->changeState(new MenuState());
}

void GameOverState::s_restartPlay(){
	Game::Instance().getStateMachine()->changeState(new PlayState());
}

bool GameOverState::onEnter(){
	if(!TextureManager::Instance().load("assets/gameover.png","gameovertext", Game::Instance().getRenderer())){
		return false;
	}

	if(!TextureManager::Instance().load("assets/menuButton.png","menuButton", Game::Instance().getRenderer())){
		return false;
	}

	if(!TextureManager::Instance().load("assets/restart.png","restart", Game::Instance().getRenderer())){
		return false;
	}


	GameObject* gameOverText = new AnimatedGraphic(new LoaderParams(200, 100, 190, 30, "gameovertext", 2), 2);
	GameObject* button1 = new MenuButton(new LoaderParams(200, 200, 200, 80, "menuButton"), s_gameOverToMain);
	GameObject* button2 = new MenuButton(new LoaderParams(200, 300, 200, 80, "restart"), s_restartPlay);

	m_gameObjects.push_back(gameOverText);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	std::cout << "Entering GameOverState\n";
	return true;
}

bool GameOverState::onExit(){
	GameState::onExit();

	TextureManager::Instance().clearFromTextureMap("gameOverText");
	TextureManager::Instance().clearFromTextureMap("menuButton");
	TextureManager::Instance().clearFromTextureMap("restart");

	std::cout << "Exiting GameOverState\n";
	return true;
}
