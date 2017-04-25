#include "PauseState.h"
#include "Game.h"
#include "GameState.h"
#include "TextureManager.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "InputHandler.h"

#include <iostream>
#include <string>

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain(){
	Game::Instance().getStateMachine()->changeState(new MenuState());
}

void PauseState::s_resumePlay(){
	Game::Instance().getStateMachine()->popState();
}

void PauseState::update(){
	GameState::update();
}

void PauseState::render(){
	std::cout << m_gameObjects.size() << std::endl;
	GameState::render();
}

bool PauseState::onEnter(){
	if(!TextureManager::Instance().load("assets/resumeButton.png", "resumeButton", Game::Instance().getRenderer())){
		return false;
	}

	if(!TextureManager::Instance().load("assets/menuButton.png", "menuButton", Game::Instance().getRenderer())){
		return false;
	}

	GameObject* button1 = new MenuButton(new LoaderParams(200, 100, 200, 80, "menuButton"), s_pauseToMain);
	GameObject* button2 = new MenuButton(new LoaderParams(200, 300, 200, 80, "resumeButton"), s_resumePlay);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	std::cout << "Entering PauseState" << std::endl;

	return true;
}

bool PauseState::onExit(){
	GameState::onExit();

	TextureManager::Instance().clearFromTextureMap("resumeButton");
	TextureManager::Instance().clearFromTextureMap("menuButton");

	InputHandler::Instance().reset();

	std::cout << "Exiting PauseState" << std::endl;
	return true;

}
