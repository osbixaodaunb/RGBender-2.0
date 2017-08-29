/*Copyright 2017 MIT*/
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

void MainMenuState::update() {
  GameState::update();
}

void MainMenuState::render() {
  GameState::render();
}

bool MainMenuState::onEnter() {
  // parse the state
  engine::StateParser stateParser;
  stateParser.parseState("test.xml", s_menuID, &m_gameObjects,
    &m_textureIDList);
  engine::AudioManager::Instance().playMusic("assets/sounds/xuxabeat.mp3");
  m_callbacks.push_back(0);  // pushback 0 callbackID starts with 1
  m_callbacks.push_back(s_menuToPlay);
  m_callbacks.push_back(s_exitFromMenu);

  setCallbacks(m_callbacks);
  INFO("Entering MainMenuState");
  return true;
}

void MainMenuState::setCallbacks(const std::vector<Callback> &callbacks) {
  // go through game objects
  for (auto gameObject : m_gameObjects) {
    /*
    / if they are of type MenuButton,
    /then assign a callback based on the id passed in from the file
    */
    if (dynamic_cast<MenuButton*>(gameObject)) {
      MenuButton* pButton = dynamic_cast<MenuButton*>(gameObject);
      pButton->setCallback(callbacks[pButton->getCallbackID()]);
    }
  }
}

bool MainMenuState::onExit() {
  GameState::onExit();
  INFO("Exiting MainMenuState");
  engine::AudioManager::Instance().stop();
  return true;
}

void MainMenuState::s_menuToPlay() {
  engine::Game::Instance().getStateMachine() -> changeState(new PlayState());
}

void MainMenuState::s_exitFromMenu() {
  engine::Game::Instance().quit();
}
