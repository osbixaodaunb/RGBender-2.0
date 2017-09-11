/*Copyright 2017 RGBender*/

#ifndef INC_CHILDBULLET_H_
#define INC_CHILDBULLET_H_

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"
#include "BaseCreator.h"
#include "Log.h"
#include "Player.h"
#include <iostream>
#include <vector>

class Player;
// Handle all necessary actions to create and manipulate a childBullet
class ChildBullet :  public engine::SDLGameObject{
 public:
    ChildBullet(Player* target);
    ~ChildBullet();

    virtual void load(engine::Vector2D pVelocity, engine::Vector2D pPosition);
    // Load pParams on the game
    void load(const engine::LoaderParams* pParams);
    void draw();
    // Update bullet status
    void update();
    void clean();
    // Verify if there  was a collision with the player
    void checkCollision();
    // Return if bullet was created and can be used
    bool isActive() {
        return m_active;
    }
    // Set bullet activate state to True.
    void setActive(bool p_active=true) {
        m_active = p_active;
    }

    void setPlayer(Player *target) {
        m_player = target;
    }

 private:
    // Aim bullet to the players position
    double rotateTowards(engine::Vector2D);
    // Velocity of the bullet
    int m_moveSpeed;

    Player *m_player;

    Uint32 timeToLive;
    Uint32 bornTime;

    bool m_active;
};

class ChildBulletCreator{
 public:
    // Create a bullet with no time to live
    ChildBullet* create(Player *target) {
        for (auto bullet : bullets) {
            if (!bullet->isActive()) {
                bullet->setActive();
                bullet->setPlayer(target);
                return bullet;
            }
        }
        INFO("A new bullet was created");
        bullets.push_back(new ChildBullet(target));
        return bullets.back();
    }

 private:
    std::vector<ChildBullet*> bullets;
};

#endif // INC_CHILDBULLET_H_
