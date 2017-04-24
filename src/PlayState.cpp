#include "PlayState.h"
#include "GameState.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "Player.h"

#include <string>
#include <iostream>

using namespace std;

const string PlayState::s_playID = "PLAY";

void PlayState::update(){
	GameState::update();
}

void PlayState::render(){
	GameState::render();
}

bool PlayState::onEnter(){	
	if(!TextureManager::Instance().load("assets/helicopter.png", "helicopter", Game::Instance().getRenderer())){
		return false;
	}

	GameObject* player = new Player(new LoaderParams(100, 100, 128, 55, "helicopter"));

	m_gameObjects.push_back(player);


	cout <<	"Entering PlayState" << endl;
	return true;
}

bool PlayState::onExit(){
	GameState::onExit();

	TextureManager::Instance().clearFromTextureMap("helicopter");

	cout << "Exiting PlayState" << endl;	
	return true;
}
