/*Copyright 2017 MIT*/
#ifndef INC_PLAYSTATE_H_
#define INC_PLAYSTATE_H_

#include "GameState.h"
#include "SDLGameObject.h"
#include "GameObject.h"
#include "Level.h"
#include "Log.h"
#include "XuxaBoss.h"
#include <string>
class PlayState : public engine::GameState {
 public:
  virtual void update();
  virtual void render();

  virtual bool onEnter();
  virtual bool onExit();

  virtual std::string getStateID() const {
    return s_playID;
  }

  engine::Level* getLevel() {
    return pLevel;
  }

 private:
  static const std::string s_playID;
  Player* m_player;
  XuxaBoss* m_boss;
  int m_playerLife = 100;
  engine::Level *pLevel = NULL;
  bool checkCollision(engine::SDLGameObject *p1, engine::SDLGameObject *p2);
};

#endif  // INC_PLAYSTATE_H_
