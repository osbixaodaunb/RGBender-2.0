/*Copyright 2017 RGBender*/

#include "Player.h"
#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "InputHandler.h"
#include "Bullet.h"
#include "Game.h"
#include "Log.h"
#include "Enemy.h"
#include "PlayState.h"
#include "Physics.h"
#include "AudioManager.h"
#include "GameOverState.h"
#include "Childmaiden.h"
#include "Timer.h"

#include <string>
#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>

#define PIXEL_MAXIMUM_VALUE 255
#define POSITION_X_AXIS 100
#define POSITION_Y_AXIS 100
/**
* Load player's scenarios elements such as bullet, health, chairs and skill
* indicator
*/
Player::Player() : SDLGameObject() {
  m_fireRate = 500; // Time between shots in milliseconds
  m_isShieldActive = false;
  m_bulletVenemous = false;

  for (int i = 1; i < 7; i++) {
    engine::TextureManager::Instance().load("assets/player_health"
    + std::to_string(i) + ".png", "health" + std::to_string(i),
    engine::Game::Instance().getRenderer());
  }

  engine::TextureManager::Instance().load("assets/ataque_protagonista_preto.png"
    , "bullet", engine::Game::Instance().getRenderer());
  engine::TextureManager::Instance().load("assets/health.png", "health",
    engine::Game::Instance().getRenderer());
  engine::TextureManager::Instance().load("assets/circle.png", "instance",
    engine::Game::Instance().getRenderer());
  engine::TextureManager::Instance().load("assets/Cadeira_frente.png",
    "chairBullet", engine::Game::Instance().getRenderer());

  INFO("Player inicializado");
  m_life = 6;
  canMove = true;
}
/**
* Load the pParams on the game
*/
void Player::load(const engine::LoaderParams* pParams) {
  SDLGameObject::load(pParams);
}
/**
* Update player skill indicator, on screen.
*/
void Player::draw() {
  engine::TextureManager::Instance().draw("instance", 100, 600, POSITION_X_AXIS, POSITION_Y_AXIS,
    engine::Game::Instance().getRenderer());
  if (m_isShieldActive) {
    engine::TextureManager::Instance().draw("shield", getPosition().getX() - 17,
      getPosition().getY() - 10, POSITION_X_AXIS + 10, POSITION_Y_AXIS + 10,
      engine::Game::Instance().getRenderer());
    engine::TextureManager::Instance().draw("brownskill", 110, 610, POSITION_X_AXIS - 20, POSITION_Y_AXIS - 20,
      engine::Game::Instance().getRenderer());
  }
  if (m_fireRate != 500) {
    engine::TextureManager::Instance().draw("redskill", 110, 610, POSITION_X_AXIS - 20, POSITION_Y_AXIS - 20,
      engine::Game::Instance().getRenderer());
  }

  if (bullet != NULL && bullet->getVenemous() == true) {
    engine::TextureManager::Instance().draw("greenskill", 110, 610, POSITION_X_AXIS - 20, POSITION_Y_AXIS - 20,
      engine::Game::Instance().getRenderer());
  }
  engine::TextureManager::Instance().draw("health" + std::to_string(m_life), 1000,
    620, POSITION_X_AXIS + 80, POSITION_Y_AXIS - 20, engine::Game::Instance().getRenderer());
  SDLGameObject::draw();
}

/**
* Verify player status.
* If is not dead, if was hitten and if the player was using shild ween hitten
*/
void Player::update() {
  if (m_life <= 0) {
    engine::Game::Instance().getStateMachine()->changeState(new GameOverState());
  }
  if (engine::Game::Instance().getStateMachine()->
    currentState()->getStateID() == "PLAY") {
    PlayState *playState = dynamic_cast<PlayState*>(engine::Game::Instance().
      getStateMachine()->currentState());
    if (playState->getLevel() != NULL && m_boss == NULL) {
      INFO("Xuxa is set");
      m_boss = playState->getLevel()->getXuxa();
    }
  }


  if (!canMove) {
    int time = engine::Timer::Instance().step() - getStunTime();
    if (time >= 700) {
      canMove = true;
    }

    rotateTowards();
  }

  if (shieldHits > 5 && m_isShieldActive) {
    engine::TextureManager::Instance().clearFromTextureMap("shield");
    shieldHits = 0;
    m_isShieldActive = false;
  }
  setPoison();

  if (canMove) {
    handleInput();
  }

  SDLGameObject::update();
}
/**
* Update bullet state as Venomous and update bullet color
* Receive as a parameter a bool that will set the m_venemous instance variable
*/
void Player::setBulletVenemous(bool isVenemous) {
  m_bulletVenemous = isVenemous;
  bullet->setVenemous(isVenemous);
  if (isVenemous == false) {
    uint8_t* pixels = new uint8_t[3];
    pixels[0] = PIXEL_MAXIMUM_VALUE;
    pixels[1] = PIXEL_MAXIMUM_VALUE;
    pixels[2] = PIXEL_MAXIMUM_VALUE;
    engine::TheTextureManager::Instance().changeColorPixels(pixels, "RAG");
  }
}
/**
* Set player's bullet to be poisoned for a period of time increasing the bullet
* hit in 5 points and verify is bullet has hitted the boss
*/
void Player::setPoison() {
  if (bullet != NULL && bullet->getVenemous() && bullet->isActive()) {
    if (engine::Timer::Instance().step() <=
        m_boss->getEnemyTime() && bullet->m_collided) {
      m_boss->takeDamage(1);
      int score = engine::Game::Instance().getScore();
      engine::Game::Instance().setScore(score + 5);
      engine::TextureManager::Instance().
      loadText(std::to_string(engine::Game::Instance().getScore()),
               "assets/fonts/Lato-Regular.ttf", "score", {PIXEL_MAXIMUM_VALUE, PIXEL_MAXIMUM_VALUE, PIXEL_MAXIMUM_VALUE}, 50,
               engine::Game::Instance().getRenderer());
      INFO(m_boss->getHealth());
    } else if (engine::Timer::Instance().step() >= m_boss->getEnemyTime()) {
      // nothing to do
    }
  }
}

void Player::clean() {
  SDLGameObject::clean();
}
/**
* Get user entries and perform actions such as movement and shoot
*/
void Player::handleInput() {
  move();

  m_numFrames = 4;
  m_currentFrame = 1;
  // Move players towards mouse if he is stoped
  // If the player is moving a vector with all the posible directions is created
  // and then it checks the current direction of the player
  if (m_velocity == engine::Vector2D(0, 0)) {
    rotateTowards();
  } else {
    engine::Vector2D vec[] = {engine::Vector2D(0, -1),
     engine::Vector2D(1, -1).norm(), engine::Vector2D(1, 0),
     engine::Vector2D(1, 1).norm(), engine::Vector2D(0, 1),
     engine::Vector2D(-1, 1).norm(),engine::Vector2D(-1, 0),
     engine::Vector2D(-1, -1).norm()
    };
    for (int i = 0; i < 8; i++) {
      if (m_velocity.norm() == vec[i]) {
        changeSprite(i);
      }
    }
    int tmp = m_currentFrame;
    m_currentFrame = 1 + int(((SDL_GetTicks() / 100) % (m_numFrames - 1)));
  }
  useSkill();
  // Verify if user is shooting and perform shoot
  if (engine::InputHandler::Instance().
    getMouseButtonState(engine::LEFT, m_fireRate)) {
    count = engine::Timer::Instance().step() + 300; // in milliseconds
    engine::AudioManager::Instance().playChunk("assets/sounds/spray.wav");
    INFO("FIRE RATE: " + m_fireRate);
    engine::Vector2D pivot = engine::Vector2D(m_width / 2 + m_position.getX(),
      m_height / 2 + m_position.getY());
    engine::Vector2D target = engine::InputHandler::Instance().
    getMousePosition() - pivot;
    target = target.norm();
    bullet =  bulletCreator.create(m_boss);
    bullet->load(target, engine::Vector2D(m_width / 2 + m_position.getX(),
                                  m_height / 2 + m_position.getY()));
    engine::Game::Instance().getStateMachine()->
    currentState()->addGameObject(bullet);
  }
}

bool inside(double angle, double value) {
  return value > angle - 22.5 && value < angle + 22.5; // 90 degrees divided by 4
}

/**
* Changes player sprite according to the keyboard press.
* It can handle all the directions the player can point to
* @params  the direction the player is moving as an integer
*/
void Player::changeSprite(int index) {
  m_flip = false;
  switch (index) {
  case 0:  // UP
    m_textureID = "up";
    break;
  case 1:  // UP-RIGHT
    m_textureID = "upright";
    break;
  case 2:  // RIGHT
    m_flip = true;
    m_textureID = "left";
    break;
  case 3:  // DOWN-RIGHT
    m_flip = true;
    m_textureID = "downleft";
    break;
  case 4:  // DOWN
    m_textureID = "down";
    break;
  case 5:  // DOWN-LEFT
    m_textureID = "downleft";
    break;
  case 6:  // LEFT
    m_textureID = "left";
    break;
  case 7:  // UP-LEFT
    m_flip = true;
    m_textureID = "upright";
    break;
  }
  // count is used here to make the attack annimation last only for a feel
  // seconds (0,3 seconds)and when the player hit the fire button.
  if (!canMove) {
    m_textureID += "stun";
  } else if (engine::Timer::Instance().step() < count) {
    m_textureID += "attack";
  }
}
/**
* Rotate the players to the mouse position
*/
void Player::rotateTowards() {
  m_numFrames = 1;
  m_currentFrame = 0;
  engine::Vector2D pivot = engine::Vector2D(m_width / 2 + m_position.getX(),
                            m_height / 2 + m_position.getY()); // player center

  engine::Vector2D target = engine::InputHandler::Instance().
  getMousePosition() - pivot; // mouse position
  target = target.norm();


  double angle = engine::Vector2D::angle(target, engine::Vector2D(0, 1));

  for (int i = 0; i < 8; i++) {
    if (inside(45 * i, angle)) {
      changeSprite(i);
      break;
    }
  }
}

/**
* Handle players movements according to keyboard press keeping
* he inside the screen, verify is the player is making a dash and
* his position on the screen
*/
void Player::move() {
  engine::Vector2D movement(0, 0);

  if (engine::InputHandler::Instance().isKeyDown("w")) {
    movement += engine::Vector2D(0, -1);
  }

  if (engine::InputHandler::Instance().isKeyDown("s")) {
    movement += engine::Vector2D(0, +1);
  }

  if (engine::InputHandler::Instance().isKeyDown("d")) {
    movement += engine::Vector2D(1, 0);
  }


  if (engine::InputHandler::Instance().isKeyDown("a")) {
    movement += engine::Vector2D(-1, 0);
  }
  movement = movement.norm();
  if (!m_isDashing) {
    m_velocity = movement * 2;
  }

  dash();
// Verify if the player is inside the screen
  if (getPosition().getY() + getHeight() >= 705) {
    if (m_velocity.getY() > 0)
      m_velocity.setY(0);
  } else if (getPosition().getY() <= 20) {
    if (m_velocity.getY() < 0)
      m_velocity.setY(0);
  }

  if (getPosition().getX() + getWidth() >= 1365) {
    if (m_velocity.getX() > 0)
      m_velocity.setX(0);
  } else if (getPosition().getX() <= -6) {
    if (m_velocity.getX() < 0)
      m_velocity.setX(0);
  }

  m_position += m_velocity;
  if (engine::Physics::Instance().checkCollision(this, m_boss)) {
    m_position -= m_velocity;
    setLife(m_life - 1);
  }

  for (auto x : engine::Game::Instance().getStateMachine()->currentState()->
       getShieldObjects()) {
    if (engine::Physics::Instance().checkCollision(this, x)) {
      if (dynamic_cast<Childmaiden*>(x)->getVisibility())
        m_position -= m_velocity;
    }
  }
}
/**
* Set m_skillManager to a specific skill enter by the user
* and update bullet sprite
*/
void Player::useSkill() {
  if (engine::InputHandler::Instance().isKeyDown("1", 200)) {
    m_skillManager.setSkillPair(&m_pSkills, RED, &isFirstSkill);
  }

  if (engine::InputHandler::Instance().isKeyDown("2", 200)) {
    m_skillManager.setSkillPair(&m_pSkills, GREEN, &isFirstSkill);
  }

  if (engine::InputHandler::Instance().isKeyDown("3", 200)) {
    m_skillManager.setSkillPair(&m_pSkills, BLUE, &isFirstSkill);
  }


  if (engine::InputHandler::Instance().isKeyDown("r", 100)) {
    std::map<std::pair<default_inks, default_inks>,
        bool>::iterator it = m_skillManager.getCoolDownMap()->find(m_pSkills);
    if (it != m_skillManager.getCoolDownMap()->end()) {
      if (it->second == false) {
        m_skillManager.setCoolDownTrigger(m_pSkills);
        if (m_pSkills.first != BLANK && m_pSkills.second != BLANK) {
          pixelColors = m_skillManager.getSkill(m_pSkills)();
          engine::TheTextureManager::Instance().
          changeColorPixels(pixelColors, "bullet");
        }
      } else {
        INFO("TA EM CD");
      }

      m_pSkills.first = BLANK;
      m_pSkills.second = BLANK;
      isFirstSkill = true;
    }
  }
}
/**
* Speed up player's speed on the direction he is moving at 15 times.
* The dash time can only last 0,1 seconds
*/
void Player::dash() {
  if (engine::InputHandler::Instance().isKeyDown("space", 1000)) {
    m_dashTime = engine::Timer::Instance().step();
    m_velocity = (m_velocity.norm() * 15);
    m_isDashing = true;
  }

  if (m_isDashing && engine::Timer::Instance().step() >= m_dashTime + 100) {
    m_isDashing = false;
  }
}
/**
* Check if the player wasn't hit so he can move
*/
void Player::setPlayerMoves(bool value) {
  canMove = value;
}
