#include "MenuState.h"
#include "MenuButton.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObject.h"
#include "PlayState.h"
#include "GameState.h"
#include "Player.h"

#include <iostream>

using namespace std;

const string MenuState::s_menuID = "MENU";

void MenuState::update(){
	GameState::update();
}

void MenuState::render(){
	GameState::render();
}

bool MenuState::onEnter(){

	if(!TextureManager::Instance().load("assets/playButton.png", "playButton", Game::Instance().getRenderer())){
		return false;
	}
	
	if(!TextureManager::Instance().load("assets/exitButton.png", "exitButton", Game::Instance().getRenderer())){
		return false;
	}


	GameObject* button1 = new MenuButton(new LoaderParams(100, 100, 400, 100, "playButton"), s_menuToPlay);
	GameObject* button2 = new MenuButton(new LoaderParams(100, 300, 400, 100, "exitButton"), s_exitFromMenu);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	cout << "Entering MenuState" << endl;
	return true;
}

bool MenuState::onExit(){
	GameState::onExit();

	TextureManager::Instance().clearFromTextureMap("playbutton");
	TextureManager::Instance().clearFromTextureMap("exitButton");
	
	cout << "Exiting MenuState" << endl;
	
	return true;
}

void MenuState::s_menuToPlay(){
	Game::Instance().getStateMachine()->changeState(new PlayState());
}

void MenuState::s_exitFromMenu(){
	Game::Instance().quit();
}
