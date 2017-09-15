/*Copyright 2017 RGBender*/

 // Class: BossBullet.h

 // Purpose: This library have all methods needed to create and manipulate a bossBullet.

#ifndef INC_BOSSBULLET_H_
#define INC_BOSSBULLET_H_

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"
#include "BaseCreator.h"
#include "Log.h"
#include <iostream>
#include <vector>

class Player;

// Class constructor method
class BossBullet : public engine::SDLGameObject {
 public:
  explicit BossBullet(Player* target);
  ~BossBullet();

  // Method that loads the velocity and the position of the bossBullet.
  void load(engine::Vector2D pVelocity, engine::Vector2D pPosition);

  // Method that load the parameter of the bossBullet.
  void load(const engine::LoaderParams* pParams);

  // Method that draws the bossBullet into the scenario.
  void draw();

  // Method that updates the bossBullet frames.
  void update();

  // Method that removes the bossBullet from the screen.
  void clean();

  // Method that checks if the bossBullet have collided with anything.
  void checkCollision();

  // Method that checks if the bossBullet is active.
  bool isActive() {
    return m_active;
  }

  // Method that sets the bossBullet as active.
  void setActive(bool p_active = true) {
    m_active = p_active;
  }

  // Method that sets the player as the target of the bossBullet shoot by the boss.
  void setPlayer(Player *target) {
    m_player = target;
  }

  // Signature of the rotateTowarsds method that sets the directions of the path of the bossBullet.
 private:
  double rotateTowards(engine::Vector2D);

  engine::Vector2D normal;
  double originTime;
  int m_moveSpeed;

  Player *m_player;

  Uint32 timeToLive;
  Uint32 bornTime;

  bool m_active;
};

// bossBullet creator class
// Creates a bossBullet, check if it's active and, if it isn't, sets it as active
class BossBulletCreator {
 public:
  BossBullet* create(Player *target) {
    for (auto bullet : bullets) {
      if (!bullet->isActive()) {
        bullet->setActive();
        bullet->setPlayer(target);
        return bullet;
      }
    }
    INFO("A new bullet was created");
    bullets.push_back(new BossBullet(target));
    return bullets.back();
  }

 private:
  std::vector<BossBullet*> bullets;
};

#endif  // INC_BOSSBULLET_H_
