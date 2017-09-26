/*Copyright 2017 RGBender*/
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

// Go from pause state to main menu state
void PauseState::s_pauseToMain() {
  engine::Game::Instance().getStateMachine() ->
  changeState(new MainMenuState());
}

// Exit pause state and resume gameplay
void PauseState::s_resumePlay() {
  engine::Game::Instance().getStateMachine() -> popState();
}

// Run in infinite loop. Updates in each frame
void PauseState::update() {
  GameState::update();
}

// Renderize information o game screen
void PauseState::render() {
  GameState::render();
}

// Routine to execute when pressing pause button and entering state
bool PauseState::onEnter() {
  engine::StateParser stateParser;

  stateParser.parseState(
   "test.xml",
   s_pauseID,
   &m_gameObjects,
   &m_textureIDList
 );

  m_callbacks.push_back(0);
  m_callbacks.push_back(s_resumePlay);

  m_callbacks.push_back(s_pauseToMain);
  setCallbacks(m_callbacks);
  INFO("Entering PauseState");

  return true;
}

// Check for type MenuButton and assign a callback based on the id
void PauseState::setCallbacks(const std::vector<Callback>& callbacks) {
  // Go through game objects
  for (auto gameObject : m_gameObjects) {
    if (dynamic_cast<MenuButton*>(gameObject)) {
      MenuButton* pButton = dynamic_cast<MenuButton*>(gameObject);
      pButton -> setCallback(callbacks[pButton -> getCallbackID()]);
    }
  }
}

// Routine to be executed after exiting state
bool PauseState::onExit() {
  GameState::onExit();

  // Clear textures and erase in screen
  engine::TextureManager::Instance().clearFromTextureMap("resumeButton");
  engine::TextureManager::Instance().clearFromTextureMap("menuButton");

  engine::InputHandler::Instance().reset();
  INFO("Exiting PauseState");
  return true;
}
