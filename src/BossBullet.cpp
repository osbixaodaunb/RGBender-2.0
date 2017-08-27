/*Copyright 2017 MIT*/
#include "BossBullet.h"
#include "SDLGameObject.h"
#include "Vector2D.h"
#include "LoaderParams.h"
#include "Timer.h"
#include "Player.h"
#include "Game.h"
#include "InputHandler.h"
#include "Log.h"
#include "Enemy.h"
#include "Physics.h"
#include "GameOverState.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


// using namespace engine;

BossBullet::~BossBullet() {
  INFO("Boss Bullet destroyed")
}

BossBullet::BossBullet(Player *target) : SDLGameObject() {
  std::srand(std::time(0));

  setPlayer(target);
  timeToLive = 5000;
  m_active = true;

  m_textureID = "bullet" + std::to_string(1 + std::rand()%9);
}

void BossBullet::load(const engine::LoaderParams* pParams) {
  std::srand(std::time(0));
  m_velocity = engine::Vector2D(0, 0);

  m_textureID = "bullet" + std::to_string(1 + std::rand()%9);
  SDLGameObject::load(pParams);
}

double BossBullet::rotateTowards(engine::Vector2D pPosition) {
  engine::Vector2D target =
      engine::InputHandler::Instance().getMousePosition() - pPosition;
  target = target.norm();

  engine::Vector2D horizontal(0, 1);

  return engine::Vector2D::angle(target, engine::Vector2D(0, 1));
}
void BossBullet::load(engine::Vector2D pVelocity, engine::Vector2D pPosition) {
  std::srand(std::time(0));
  double m_angle = 0;

  m_moveSpeed = 3;
  m_textureID = "bullet" + std::to_string(1 + std::rand()%9);
  engine::LoaderParams* pParams = new engine::LoaderParams(pPosition.getX(),
          pPosition.getY(), 48, 48, m_textureID,
          0, 0, 0, m_angle);
  SDLGameObject::load(pParams);

  m_currentFrame = 0;
  bornTime = engine::Timer::Instance().step();
  m_velocity = pVelocity.norm() * m_moveSpeed;
  // m_velocity = Vector2D(0.5, 0.5);

  engine::Vector2D norm = pVelocity.norm();
  normal = engine::Vector2D(norm.getY(), -norm.getX());
  originTime = engine::Timer::Instance().step();
}

void BossBullet::draw() {
  SDLGameObject::draw();
}

void BossBullet::update() {
  engine::Vector2D tmp = m_velocity;

  double sign = sin((engine::Timer::Instance().step() - originTime)/125);
  sign /= fabs(sign);

  sign *= 1;
  m_velocity += engine::Vector2D(normal.getX()*sign, normal.getY()*sign);

  m_position += m_velocity;
  m_velocity = tmp;



  if (engine::Timer::Instance().step() >= bornTime + timeToLive) {
    m_active = false;
    engine::Game::Instance().getStateMachine()->
        currentState()->removeGameObject(this);
  }

  checkCollision();
}

void BossBullet::checkCollision() {
  if (m_active) {
    engine::Vector2D pos = m_player->getPosition();
    engine::Vector2D thisPos = getPosition();

    if (engine::Physics::Instance().checkCollision(
          dynamic_cast<SDLGameObject*>(m_player),
          dynamic_cast<SDLGameObject*>(this))) {
      m_active = false;
      engine::Game::Instance().getStateMachine()->currentState()->
          removeGameObject(this);
      // INFO("Bullet collided");
      // INFO("PLAYER LOST THE GAME");
    if (!m_player->getShieldActive()) {
        m_player->setLife((m_player->getLife()) - 1);
      } else {
        if (m_player->getShieldActive()) {
        m_player->setShieldHits();
        }
      }
      // Game::Instance().getStateMachine()->changeState(new GameOverState());
    }
  }
}

void BossBullet::clean() {
  SDLGameObject::clean();
}

