/*Copyright 2017 MIT*/
#ifndef INC_MENUBUTTON_H_
#define INC_MENUBUTTON_H_

#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "BaseCreator.h"

class MenuButton : public engine::SDLGameObject {
 public:
  MenuButton();

  void load(const engine::LoaderParams* pParams);

  void setCallback(void(*callback)()) {
    m_callback = callback;
  }

  int getCallbackID() {
    return m_callbackID;
  }

  virtual void draw();
  virtual void update();
  virtual void clean();

 private:
  enum button_state {
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
    CLICKED = 2
  };

  void (*m_callback)();
  bool m_bReleased;
  int m_callbackID;
};

class MenuButtonCreator : public engine::BaseCreator {
  engine::GameObject* createGameObject() const {
    return new MenuButton();
  }
};

#endif  // INC_MENUBUTTON_H_
