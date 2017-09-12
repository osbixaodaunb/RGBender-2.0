/*Copyright 2017 RGBender*/
#include "PlayState.h"
#include "GameState.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "Player.h"
#include "PauseState.h"
#include "InputHandler.h"
#include "Enemy.h"
#include "GameOverState.h"
#include "SDLGameObject.h"
#include "StateParser.h"
#include "AudioManager.h"
#include "Level.h"
#include "LevelParser.h"
#include "Log.h"
#include <string>
#include <iostream>

// using namespace std;
// using namespace engine;

const std::string PlayState::s_playID = "PLAY";

// Routine to be executed in loop, updated after each frame
void PlayState::update() {

  if (engine::InputHandler::Instance().isKeyDown("p")) {
    engine::Game::Instance().getStateMachine() -> pushState(new PauseState());
  }

  GameState::update();

  if (pLevel != NULL) {
    pLevel -> update();
  }

  m_playerLife = m_player->getLife();

  // if(checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]),
  //   dynamic_cast<SDLGameObject*>(m_gameObjects[1]))){
  //   Game::Instance().getStateMachine()->pushState(new GameOverState());
  // }
}

// Renderize information on screen. It shows and displays.
void PlayState::render() {
  if (pLevel != NULL) {
    pLevel->render();
  }

  // Draw boss heath bar on screen
  engine::TextureManager::Instance().draw(
    "emptyhealthboss",
    500,
    m_boss -> getPosition().getY() - 77,
    424,
    60,
    engine::Game::Instance().getRenderer()
  );

  // Draw Boss health bar on screen
  engine::TextureManager::Instance().draw(
    "healthboss",
    500 + 11,
    m_boss -> getPosition().getY() - 60,
    m_boss -> getHealth() - 20,
    28,
    engine::Game::Instance().getRenderer()
  );

  // Draw madreXuxa name on screen
  engine::TextureManager::Instance().draw(
    "madreXuxa",
    620,
    m_boss -> getPosition().getY() - 120,
    180,
    60,
    engine::Game::Instance().getRenderer()
  );

  GameState::render();
}

// Routine to execute when entering game. Starting to play.
bool PlayState::onEnter() {
  /*
  * stateParser.parseState("test.xml",
  *    s_playID,
  *    &m_gameObjects,
  *    &m_textureIDList);
  */
  engine::Game::Instance().setScore(0);

  // Load Score and displays it on screen using ttf font
  engine::TextureManager::Instance().loadText(
    std::to_string(engine::Game::Instance().getScore()),
    "assets/fonts/Lato-Regular.ttf",
    "score",
    {0, 0, 0},
    50,
    engine::Game::Instance().getRenderer()
  );

  // Plays background music
  engine::AudioManager::Instance().playMusic("assets/sounds/xuxabeat.mp3");

  // Parse level from xml file
  engine::LevelParser levelParser;
  pLevel = levelParser.parseLevel("assets/mapadoidao.tmx");

  m_player = pLevel -> getPlayer();
  m_boss = pLevel -> getXuxa();

  INFO("Entering PlayState");
  return true;
}

// Routine to be executed after exiting state
bool PlayState::onExit() {
  GameState::onExit();

  // Stop music
  engine::AudioManager::Instance().stop();

  // Clear textures erasing from screen
  engine::TextureManager::Instance().clearFromTextureMap("helicopter");
  engine::TextureManager::Instance().clearFromTextureMap("RAG");

  INFO("Exiting PlayState");
  return true;
}

// Check for collisions between two game objects
bool PlayState::checkCollision(engine::SDLGameObject *p1,
  engine::SDLGameObject *p2) {

  // Variable Declarations
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;

  // Logics and position calculations
  leftA = p1 -> getPosition().getX();
  rightA = p1 -> getPosition().getX() + p1 -> getWidth();
  topA = p1 -> getPosition().getY();
  bottomA = p1 -> getPosition().getY() + p1 -> getHeight();

  leftB = p2 -> getPosition().getX();
  rightB = p2 -> getPosition().getX() + p2 -> getWidth();
  topB = p2 -> getPosition().getY();
  bottomB = p2 -> getPosition().getY() + p2 -> getHeight();

  // Check if positions are overriding each other
  if (bottomA <= topB) return false;
  if (topA >= bottomB) return false;
  if (rightA <= leftB) return false;
  if (leftA >= rightB) return false;

  return true;
}
