#include "GameState.h"
#include "GameObject.h"

#include <iostream>

void GameState::update(){
	for(auto gameObject : m_gameObjects){
		gameObject->update();
	}
}

void GameState::render(){
	for(auto gameObject : m_gameObjects){
		gameObject->draw();
	}
}

bool GameState::onExit(){
	for(auto gameObject : m_gameObjects){
		gameObject->clean();
	}

	m_gameObjects.clear();

	return true;
}
