/*Copyright 2017 MIT*/
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

const std::String WinGameState::s_winGameID = "WIN";

void WinGameState::s_winGameToMain() {
  engine::Game::Instance().getStateMachine()->changeState(new MainMenuState());
}

void WinGameState::update() {
  GameState::update();
}

void WinGameState::render() {
  GameState::render();
}

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

void WinGameState::setCallbacks(const std::vector<Callback>& callbacks) {
  for (auto gameObject : m_gameObjects) {
    if (dynamic_cast<MenuButton*>(gameObject)) {
      MenuButton* pButton = dynamic_cast<MenuButton*>(gameObject);
      pButton->setCallback(callbacks[pButton->getCallbackID()]);
    }
  }
}

bool WinGameState::onExit() {
  GameState::onExit();

  engine::TextureManager::Instance().clearFromTextureMap("menuButton");

  engine::InputHandler::Instance().reset();
  INFO("Exiting WinGameState");
  return true;
}
