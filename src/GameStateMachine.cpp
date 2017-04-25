#include "GameStateMachine.h"

#include <iostream>

void GameStateMachine::pushState(GameState* pState){
	m_gameStates.push_back(pState);
	m_gameStates.back()->onEnter();
}

void GameStateMachine::popState(){
	if(!m_gameStates.empty()){
		if(m_gameStates.back()->onExit()){
			auto tmp = m_gameStates.back();
			m_gameStates.pop_back();
			delete tmp;
		}
	}
}

void GameStateMachine::changeState(GameState* pState){
	if(!m_gameStates.empty()){
		if(m_gameStates.back()->getStateID() == pState->getStateID()){
			return;
		}

		popState();
	}

	m_gameStates.push_back(pState);

	m_gameStates.back()->onEnter();
}

void GameStateMachine::update(){
	if(!m_gameStates.empty()){
		m_gameStates.back()->update();
	}
}

void GameStateMachine::render(){
	if(!m_gameStates.empty()){
		m_gameStates.back()->render();
	}
}
