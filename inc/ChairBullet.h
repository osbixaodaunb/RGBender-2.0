/*Copyright 2017 RGBender*/

// Library: ChairBullet (.h)

// Purpose: This library declares methods that will be used later in
// the ChairBullet.cpp file.

#ifndef INC_CHAIRBULLET_H_
#define INC_CHAIRBULLET_H_

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"
#include "BaseCreator.h"
#include "Log.h"
#include "Player.h"
#include <iostream>
#include <vector>

class Player;

// Class constructor method.
class ChairBullet :

public engine::SDLGameObject{
 public:
    ChairBullet(Player* target);
    ~ChairBullet();

    // Method that loads the velocity and the position of the chair bullet.
    virtual void load(engine::Vector2D pVelocity, engine::Vector2D pPosition);
    // Method that load the parameter of the chair bullet.
    void load(const engine::LoaderParams* pParams);
    // Method that draws the chair bullet.
    void draw();
    // Method that updates chair bullet frames.
    void update();
    // Method that celans the chair bullet of the screen.
    void clean();
    // Method that updates the previous methods.
    void checkCollision();

    bool isActive() {
      return m_active;
    }

    // Method that considers the chair bullet collision with the child.
    void setActive(bool p_active = true) {
      m_active = p_active;
    }
    // Method that sets the child as chair bullet target.
    void setPlayer(Player *target) {
      m_player = target;
    }

 private:
    // Signature of the rotateTowards method which gives direction to the chair bullet.
    double rotateTowards(engine::Vector2D);

    int m_moveSpeed;

    Player *m_player;

    Uint32 timeToLive;
    Uint32 bornTime;

    bool m_active;
};

class ChairBulletCreator{
 public:
     ChairBullet* create(Player *target) {
         for (auto bullet : bullets) {
             if (!bullet->isActive()) {
                 bullet->setActive();
                 bullet->setPlayer(target);
                 return bullet;
             }
         }
         INFO("A new bullet was created");
         bullets.push_back(new ChairBullet(target));
         return bullets.back();
     }

 private:
     std::vector<ChairBullet*> bullets;
};

#endif  // INC_CHAIRBULLET_H_
