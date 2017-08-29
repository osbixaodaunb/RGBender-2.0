/*Copyright 2017 MIT*/
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

// using namespace engine;

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update() {
  GameState::update();
}

void GameOverState::render() {
  GameState::render();
}

void GameOverState::s_gameOverToMain() {
  engine::Game::Instance().getStateMachine() ->
    changeState(new MainMenuState());
}

void GameOverState::s_restartPlay() {
  engine::Game::Instance().getStateMachine() -> changeState(new PlayState());
}

bool GameOverState::onEnter() {
  engine::StateParser stateParser;
  stateParser.parseState("test.xml", s_gameOverID, &m_gameObjects,
    &m_textureIDList);

  m_callbacks.push_back(0);
  m_callbacks.push_back(s_gameOverToMain);
  m_callbacks.push_back(s_restartPlay);

  // set the callbacks for menu items
  setCallbacks(m_callbacks);
  INFO("Entering GameOverState");
  return true;
}

bool GameOverState::onExit() {
  GameState::onExit();
  INFO("Exiting GameOverState");
  return true;
}

void GameOverState::setCallbacks(const std::vector<Callback> &callbacks) {
  // go through game objects
  for (auto gameObject : m_gameObjects) {
    /*
    / if they are of type MenuButton,
    / then assign a callback based on the id passed in from the file
    */
    if (dynamic_cast<MenuButton*>(gameObject)) {
      MenuButton* pButton = dynamic_cast<MenuButton*>(gameObject);
      pButton -> setCallback(callbacks[pButton -> getCallbackID()]);
    }
  }
}
