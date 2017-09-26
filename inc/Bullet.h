/*Copyright 2017 RGBender*/

// Class: Bullet (.h)

// Purpose: This class declares methods that will be used later in
// the Bullet.cpp file.

#ifndef INC_BULLET_H_
#define INC_BULLET_H_

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"
#include "BaseCreator.h"
#include "Log.h"
#include <iostream>
#include <vector>

class Enemy;

// Class constructor method.
class Bullet : public engine::SDLGameObject{
 public:
  explicit Bullet(Enemy* p_boss);
  ~Bullet();

  // Method that loads the velocity and the position of the bullet.
  void load(engine::Vector2D pVelocity, engine::Vector2D pPosition);
  // Method that load the parameter of the bullet.
  void load(const engine::LoaderParams* pParams);
  // Method that draws the bullet.
  void draw();
  // Method that updates bullet frames.
  void update();
  // Method that celans the bullet of the screen.
  void clean();
  // Method that updates the previous methods.
  void checkCollision();

  // Returns the active value of the bullet.
  bool isActive() {
    return m_active;
  }

  // Method that considers the bullet collision with the boss.
  void setActive(bool p_active = true) {
    m_active = p_active;
  }
  void setBoss(Enemy *p_boss) {
    m_boss = p_boss;
  }
  // Method that loads the poison special.
  void setVenemous(bool isVenemous) {
    m_venemous = isVenemous;
  }
  // Method that put the poison in the bullet.
  // Returns the poison.
  bool getVenemous() {
    return m_venemous;
  }
  bool m_collided;

 private:
  // Signature of the rotateTowards method that directs
  // the bullet to the mouse cursor.
  double rotateTowards(engine::Vector2D);
  int m_moveSpeed;
  bool m_venemous = false;
  Enemy *m_boss;

  Uint32 timeToLive;
  Uint32 bornTime;

  bool m_active;
};

// Creates the bullet.
// Returns the bullet and a new bullet after.
class BulletCreator {
 public:
  Bullet* create(Enemy *p_boss) {
    for (auto bullet : bullets) {
      if (!bullet->isActive()) {
        bullet->setActive();
        bullet->setBoss(p_boss);
        return bullet;
      }
    }
    INFO("A new bullet was created");
    bullets.push_back(new Bullet(p_boss));
    return bullets.back();
  }

 private:
    std::vector<Bullet*> bullets;
};

#endif  // INC_BULLET_H_
