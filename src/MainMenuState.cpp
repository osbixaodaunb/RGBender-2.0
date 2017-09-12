/*Copyright 2017 RGBender*/
#include "MainMenuState.h"
#include "MenuButton.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObject.h"
#include "PlayState.h"
#include "GameState.h"
#include "Player.h"
#include "StateParser.h"
#include "Log.h"
#include <vector>
#include <iostream>
#include "AudioManager.h"

// using namespace std;
// using namespace engine;

const std::string MainMenuState::s_menuID = "MENU";

// Run on infite loop, update in each frame
void MainMenuState::update() {
  GameState::update();
}

// Renderize information on game screen
void MainMenuState::render() {
  GameState::render();
}

// Routine to be executed before changing to state
bool MainMenuState::onEnter() {
  // Parse the state
  engine::StateParser stateParser;
  stateParser.parseState("test.xml", s_menuID, &m_gameObjects,
    &m_textureIDList);

  // Play background music
  engine::AudioManager::Instance().playMusic("assets/sounds/xuxabeat.mp3");

  // Callback to insert buttons in state
  m_callbacks.push_back(0);
  m_callbacks.push_back(s_menuToPlay);
  m_callbacks.push_back(s_exitFromMenu);

  setCallbacks(m_callbacks);
  INFO("Entering MainMenuState");
  return true;
}

// Check for type MenuButton and assign a callback based on the id
void MainMenuState::setCallbacks(const std::vector<Callback> &callbacks) {
  // Go through game objects
  for (auto gameObject : m_gameObjects) {
    if (dynamic_cast<MenuButton*>(gameObject)) {
      MenuButton* pButton = dynamic_cast<MenuButton*>(gameObject);
      pButton->setCallback(callbacks[pButton->getCallbackID()]);
    }
  }
}

// Routine to be executed after exiting state
bool MainMenuState::onExit() {
  GameState::onExit();
  INFO("Exiting MainMenuState");
  engine::AudioManager::Instance().stop();
  return true;
}

// Change from scene menu to scene Play, where the game starts
void MainMenuState::s_menuToPlay() {
  engine::Game::Instance().getStateMachine() -> changeState(new PlayState());
}

// Quit game after pressing the respective buttons
void MainMenuState::s_exitFromMenu() {
  engine::Game::Instance().quit();
}
