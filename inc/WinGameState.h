/*Copyright 2017 MIT*/
#ifndef INC_WINGAMESTATE_H_
#define INC_WINGAMESTATE_H_

#include "GameObject.h"
#include "MenuState.h"

#include <string>
#include <vector>

class WinGameState : public MenuState{
 public:
  virtual void update();
  virtual void render();

  virtual bool onEnter();
  virtual bool onExit();

  virtual std::string getStateID() const {
    return s_winGameID;
  }

  static void s_winGameToMain();
 private:
  virtual void setCallbacks(const std::vector<Callback>& callbacks);

  static const std::string s_winGameID;
};

#endif  // INC_WINGAMESTATE_H_
