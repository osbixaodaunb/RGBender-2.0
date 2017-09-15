/*Copyright 2017 MIT*/
#include "PauseState.h"
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
#include <vector>

// using namespace engine;

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain() {
  engine::Game::Instance().getStateMachine() ->
  changeState(new MainMenuState());
}

void PauseState::s_resumePlay() {
  engine::Game::Instance().getStateMachine() -> popState();
}

void PauseState::update() {
  GameState::update();
}

void PauseState::render() {
  GameState::render();
}

bool PauseState::onEnter() {
  engine::StateParser stateParser;
  stateParser.parseState("test.xml",
   s_pauseID,
   &m_gameObjects,
   &m_textureIDList);

  m_callbacks.push_back(0);
  m_callbacks.push_back(s_resumePlay);

  m_callbacks.push_back(s_pauseToMain);
  setCallbacks(m_callbacks);
  INFO("Entering PauseState");

  return true;
}

void PauseState::setCallbacks(const std::vector<Callback>& callbacks) {
  for (auto gameObject : m_gameObjects) {
    if (dynamic_cast<MenuButton*>(gameObject)) {
      MenuButton* pButton = dynamic_cast<MenuButton*>(gameObject);
      pButton -> setCallback(callbacks[pButton -> getCallbackID()]);
    }
  }
}

bool PauseState::onExit() {
  GameState::onExit();

  engine::TextureManager::Instance().clearFromTextureMap("resumeButton");
  engine::TextureManager::Instance().clearFromTextureMap("menuButton");

  engine::InputHandler::Instance().reset();
  INFO("Exiting PauseState");
  return true;
}
