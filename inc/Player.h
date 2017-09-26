/*Copyright 2017 RGBender*/

/**
* Player class header <Players.h>
* <p>Responsable for creating player, handle inputs from keyboard.</p>
*/

#ifndef INC_PLAYER_H_
#define INC_PLAYER_H_

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "BaseCreator.h"
#include "SkillManager.h"
#include "Timer.h"
#include "Bullet.h"

#include <vector>
#include <string>
#include <SDL2/SDL.h>

class Enemy;
/**
* Responsable for creating player, handle inputs from keyboard
*/
class Player : public engine::SDLGameObject {
 public:
  Player();
  /**
  * Change the player sprinte according to the number passed as parameter
  * @params integer corresponting ta a direction
  */
  void changeSprite(int);
  /**
  * Load pParams on the game
  */
  void load(const engine::LoaderParams* pParams);
  void draw();
  /**
  * Update player status
  */
  void update();
  void clean();
  typedef uint8_t*(*Callback) ();
  uint8_t* pixelColors;
  /**
  * Defines time between shots
  * @params integer fireRate in milliseconds
  */
  void setFireRate(int fireRate) {
    m_fireRate = fireRate;
  }
  /**
  * Defines player's life. Doesn't verify it is bigger then 6i
  * @params integer life
  */
  void setLife(int life) {
    m_life = life;
  }
  /**
  * Get players life
  * @return player's life
  */
  int getLife() {
    return m_life;
  }
  Bullet* getPlayerBullet() {
    return bullet;
  }
  /**
  * Increase how many damage a shield can take by 1
  */
  void setShieldHits() {
    shieldHits++;
  }
  int getShieldHits() {
    return shieldHits;
  }
  void setActiveShield(bool isActive) {
    m_isShieldActive = isActive;
  }
  bool getShieldActive() {
    return m_isShieldActive;
  }
  /**
  * Make players bullet venomous
  */
  void setBulletVenemous(bool isVenemous);
  /**
  * Handle poisoned bullet
  */
  void setPoison();
  /**
  * Define if the player can move or not
  */
  void setPlayerMoves(bool);
  /**
  * how much time the player will not move in milliseconds
  */
  void setStunTime(int value) {
    stunTime = value;
  }

  int getStunTime() {
    return stunTime;
  }
  bool getBulletVenemous() {
    return m_bulletVenemous;
  }

 private:
  Bullet *bullet = NULL;
  bool m_isShieldActive;
  int shieldHits = 0;
  bool m_bulletVenemous;
  int count = 0; // The time that attack sprite is activated
  /**
  * Handle all possibles user inputs
  */
  void handleInput();
  SkillManager m_skillManager = SkillManager(this);
  std::pair<default_inks, default_inks> m_pSkills;
  bool isFirstSkill = true;
  /**
  * Take care of players position on screen
  */
  void move();
  /**
  * Points the player to the mouse
  */
  void rotateTowards();
  void dash();
  void useSkill();
  bool canMove;
  int stunTime;
  int m_life;
  Uint32 m_time;
  bool m_isDashing;
  Uint32 m_dashTime;
  int m_fireRate;
  BulletCreator bulletCreator;

  Enemy* m_boss = NULL;
};

class PlayerCreator : public engine::BaseCreator {
  engine::GameObject* createGameObject() const {
    return new Player();
  }
};

#endif  // INC_PLAYER_H_
