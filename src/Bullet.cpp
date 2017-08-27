/*Copyright 2017 MIT*/
#include "Bullet.h"
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
#include <iostream>
#include <string>
#include "Childmaiden.h"

// using namespace engine;

Bullet::~Bullet() {
  INFO("Bullet destroyed")
}

Bullet::Bullet(Enemy *p_boss) : SDLGameObject() {
  setBoss(p_boss);

  timeToLive = 1000;
  m_active = true;
  m_venemous = false;
}

void Bullet::load(const engine::LoaderParams* pParams) {
  m_velocity = engine::Vector2D(0, 0);

  SDLGameObject::load(pParams);
}

double Bullet::rotateTowards(engine::Vector2D pPosition) {
  engine::Vector2D target = engine::InputHandler::Instance().
      getMousePosition() - pPosition;
  target = target.norm();

  engine::Vector2D horizontal(0, 1);

  return engine::Vector2D::angle(target, engine::Vector2D(0, 1));
}
void Bullet::load(engine::Vector2D pVelocity, engine::Vector2D pPosition) {
  double angle = rotateTowards(pPosition);

  m_moveSpeed = 5;
  engine::LoaderParams* pParams = new engine::LoaderParams(pPosition.getX(),
          pPosition.getY(),
       16, 16, "bullet", 0, 0, 0, angle);
  SDLGameObject::load(pParams);

  m_currentFrame = 0;
  bornTime = engine::Timer::Instance().step();
  m_velocity = pVelocity.norm() * m_moveSpeed;
}

void Bullet::draw() {
  SDLGameObject::draw();
}

void Bullet::update() {
  // std::cout << "Bullet top: " << getPosition().getY() +
  // (getHeight() - getCollider().getHeight())/2 << std::endl;
  m_position += m_velocity;
  m_currentFrame = static_cast<int>(((SDL_GetTicks() / (300)) % 4));
  if (engine::Timer::Instance().step() >= bornTime + timeToLive) {
    m_active = false;
    m_venemous = false;
    engine::Game::Instance().getStateMachine()->currentState()->
        removeGameObject(this);
  }
  checkCollision();
}

void Bullet::checkCollision() {
  if (m_active) {
    engine::Vector2D pos = m_boss->getPosition();
    engine::Vector2D thisPos = getPosition();

    for (auto obj : engine::Game::Instance().getStateMachine()->
                  currentState()->getShieldObjects()) {
      if (engine::Physics::Instance().
              checkCollision(dynamic_cast<SDLGameObject*>(obj),
                  dynamic_cast<SDLGameObject*>(this))) {
        if (dynamic_cast<Childmaiden*>(obj)->getVisibility()) {
          INFO("REMOVENDO BALA");
          m_active = false;
          engine::Game::Instance().getStateMachine()->
              currentState()->removeGameObject(this);
          INFO("Bullet collided with shield");
        } else {
          break;
        }
      }
    }

    if (engine::Physics::Instance().
            checkCollision(dynamic_cast<SDLGameObject*>(m_boss),
                dynamic_cast<SDLGameObject*>(this))) {
      m_active = false;
      engine::Game::Instance().getStateMachine()->currentState()->
          removeGameObject(this);
      m_boss->takeDamage(10);
      if (m_venemous) {
        INFO("VENEMOUS TRUE");
        m_collided = true;
        uint8_t* pixels = new uint8_t[3];
        pixels[0] = 152;
        pixels[1] = 255;
        pixels[2] = 156;
        engine::TheTextureManager::Instance().changeColorPixels(pixels, "RAG");
        m_boss->setEnemyTime(1000);
      }

      int score = engine::Game::Instance().getScore();
      engine::Game::Instance().setScore(score + 10);
      engine::TextureManager::Instance().
          loadText(std::to_string(engine::Game::Instance().getScore()),
          "assets/fonts/Lato-Regular.ttf", "score",
          {255, 255, 255}, 50, engine::Game::Instance().getRenderer());
      INFO("Bullet collided with boss");
    }
  }
}

void Bullet::clean() {
  SDLGameObject::clean();
}

