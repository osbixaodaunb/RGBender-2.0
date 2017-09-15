/*Copyright 2017 RGBender*/

// Class: Childmaiden (.cpp)

// Purpose: This class provides functionalities for the children shield.

#include "Childmaiden.h"
#include <math.h>
#include "Vector2D.h"
#include "Game.h"
#include "SDLGameObject.h"
#include <iostream>
#include "Timer.h"

// Configures the position of the child.
engine::Vector2D posToRound(630, 210);

// Sets visibility for the child.
Childmaiden::Childmaiden() {
  isVisible = true;
  sinalx = 1;
  sinaly = 1;
  engine::Game::Instance().getStateMachine()->
    currentState()->addShieldObject(this);
  m_velocity = engine::Vector2D(0, 0);
  originTime = engine::Timer::Instance().step();
}

// Multiplies the child, forming a circle-shaped shield around the boss.
engine::Vector2D rotateVec(engine::Vector2D vec, double ang) {
  engine::Vector2D result;

  result.setX(vec.getX() * cos(ang) - vec.getY() * sin(ang));
  result.setY(vec.getX() * sin(ang) + vec.getY() * cos(ang));

  return result;
}

// Updates the child frames.
void Childmaiden::update() {
  m_currentFrame = static_cast<int>(((SDL_GetTicks() / 300) % m_numFrames));
  m_position = posToRound + rotateVec(startPoint,
    (engine::Timer::Instance().step() - originTime) / 1000.0);
}

// Loads parameters such as the distance between the children and how much
// children will be in the shield.
void Childmaiden::load(const engine::LoaderParams *pParams) {
  SDLGameObject::load(pParams);

  std::vector<SDLGameObject*> v = engine::Game::Instance().getStateMachine()->
    currentState()->getShieldObjects();
  for (int i = 0; i < v.size(); i++) {
    if (this == dynamic_cast<Childmaiden*>(v[i])) {
      engine::Vector2D vec(0, 130);
      m_position = posToRound + rotateVec(vec, 72 * i);
      std::cout << v.size() << std::endl;
    }
  }

  startPoint = m_position - posToRound;
}

// Draws the children in the screen.
void Childmaiden::draw() {
  if (isVisible)
    SDLGameObject::draw();
}

// Cleans the children from the screen.
void Childmaiden::clean() {
  SDLGameObject::clean();
}
