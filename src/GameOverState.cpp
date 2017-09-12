/*Copyright 2017 RGBender*/
#include "GameOverState.h"
#include "GameState.h"
#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "StateParser.h"
#include "Log.h"

#include <iostream>

const std::string GameOverState::s_gameOverID = "GAMEOVER";

// Run on infite loop
void GameOverState::update() {
  GameState::update();
}

// Renderize information on screen
void GameOverState::render() {
  GameState::render();
}

// Change to state of main menu after losing
void GameOverState::s_gameOverToMain() {
  engine::Game::Instance().getStateMachine() ->
    changeState(new MainMenuState());
}

// Restart game. Play again instead of going to main menu
void GameOverState::s_restartPlay() {
  engine::Game::Instance().getStateMachine() -> changeState(new PlayState());
}

// Routine to be executed before changing to state
bool GameOverState::onEnter() {
  engine::StateParser stateParser;
  stateParser.parseState("test.xml", s_gameOverID, &m_gameObjects,
    &m_textureIDList);

  m_callbacks.push_back(0);
  m_callbacks.push_back(s_gameOverToMain);
  m_callbacks.push_back(s_restartPlay);

  // Insert callbacks for menu items and objects
  setCallbacks(m_callbacks);
  INFO("Entering GameOverState");
  return true;
}

// Routine to be executed after exiting state
bool GameOverState::onExit() {
  GameState::onExit();
  INFO("Exiting GameOverState");
  return true;
}

void GameOverState::setCallbacks(const std::vector<Callback> &callbacks) {
  // Go through game objects
  for (auto gameObject : m_gameObjects) {
    // Check for type menuButton, assign a callback based on the btn ID
    if (dynamic_cast<MenuButton*>(gameObject)) {
      MenuButton* pButton = dynamic_cast<MenuButton*>(gameObject);
      pButton -> setCallback(callbacks[pButton -> getCallbackID()]);
    }
  }
}
