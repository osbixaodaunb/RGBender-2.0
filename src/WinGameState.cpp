/*Copyright 2017 RGBender*/
#include "WinGameState.h"
#include "Game.h"
#include "GameState.h"
#include "TextureManager.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "StateParser.h"
#include "Log.h"
#include <iostream>
#include <string>

const std::string WinGameState::s_winGameID = "WIN";


/**
* This method change to main menu after a victory
*/
void WinGameState::s_winGameToMain() {
  engine::Game::Instance().getStateMachine()->changeState(new MainMenuState());
}


/**
* This method update the frame in WinGame State
*/
void WinGameState::update() {
  GameState::update();
}

/**
* This method render a frame in WinGame state
*/
void WinGameState::render() {
  GameState::render();
}

/**
* This method do the necessary routine to enter in WinGame state
*/
bool WinGameState::onEnter() {
  engine::StateParser stateParser;
  stateParser.parseState(
    "test.xml", s_winGameID, &m_gameObjects, &m_textureIDList);

  m_callbacks.push_back(0);
  m_callbacks.push_back(s_winGameToMain);

  setCallbacks(m_callbacks);
  INFO("Entering WinGameState");

  return true;
}

/**
* This method set the set of callbacks
* @param callbacks vector of callbacks sequence
*/

void WinGameState::setCallbacks(const std::vector<Callback>& callbacks) {
  for (auto gameObject : m_gameObjects) {
    if (dynamic_cast<MenuButton*>(gameObject)) {
      MenuButton* pButton = dynamic_cast<MenuButton*>(gameObject);
      pButton->setCallback(callbacks[pButton->getCallbackID()]);
    }
  }
}

/**
* This method clear the texture of menuButton and exit Win Game state
*/
bool WinGameState::onExit() {
  GameState::onExit();

  engine::TextureManager::Instance().clearFromTextureMap("menuButton");

  engine::InputHandler::Instance().reset();
  INFO("Exiting WinGameState");
  return true;
}
