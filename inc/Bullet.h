/*Copyright 2017 MIT*/
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

class Bullet : public engine::SDLGameObject{
 public:
  Bullet(Enemy* p_boss);
  ~Bullet();

  void load(engine::Vector2D pVelocity, engine::Vector2D pPosition);
  void load(const engine::LoaderParams* pParams);
  void draw();
  void update();
  void clean();
  void checkCollision();

  bool isActive() {
    return m_active;
  }

  void setActive(bool p_active = true) {
    m_active = p_active;
  }

  void setBoss(Enemy *p_boss) {
    m_boss = p_boss;
  }
  void setVenemous(bool isVenemous) {
    m_venemous = isVenemous;
  }

  bool getVenemous() {
    return m_venemous;
  }
  bool m_collided;

 private:
  double rotateTowards(engine::Vector2D);
  int m_moveSpeed;
  bool m_venemous = false;
  Enemy *m_boss;

  Uint32 timeToLive;
  Uint32 bornTime;

  bool m_active;
};

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
