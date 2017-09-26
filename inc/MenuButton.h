/*Copyright 2017 MIT*/

// Class: MenuButton (.h)

// Purpose: this class declares methods that will be used
// later in the MenuButton.cpp file.

#ifndef INC_MENUBUTTON_H_
#define INC_MENUBUTTON_H_

#include "LoaderParams.h"
#include "SDLGameObject.h"
#include "BaseCreator.h"

// Class constructor method.
class MenuButton : public engine::SDLGameObject {
 public:
  MenuButton();

  // Method that loads the parameters of the menu button.
  void load(const engine::LoaderParams* pParams);

  // Makes the transition between the menu button and the beginning of the game.
  void setCallback(void(*callback)()) {
    m_callback = callback;
  }

  // Returns the beginning of the game.
  int getCallbackID() {
    return m_callbackID;
  }

  // Draws the menu button.
  virtual void draw();
  // Updates the frames of th menu button.
  virtual void update();
  // Cleans the menu button of the screen.
  virtual void clean();

 private:
  // Changes the state of the button according with the mouse cursor.
  enum button_state {
    MOUSE_OUT = 0,
    MOUSE_OVER = 1,
    CLICKED = 2
  };

  // Parameter to start the game.
  void (*m_callback)();
  bool m_bReleased;
  int m_callbackID;
};

// Creates the menu button.
// Returns a new menu button.
class MenuButtonCreator : public engine::BaseCreator {
  engine::GameObject* createGameObject() const {
    return new MenuButton();
  }
};

#endif  // INC_MENUBUTTON_H_
