/*Copyright 2017 MIT*/

// Class: MenuButton (.cpp)

// Purpose: This class provides functionalities for the menu button.

#include "MenuButton.h"
#include "Vector2D.h"
#include "InputHandler.h"

MenuButton::MenuButton() : SDLGameObject() {
}

// Load the parameters of the menu button such as start the game and change
// the state of the button according to the mouse cursor position.
void MenuButton::load(const engine::LoaderParams* pParams) {
  SDLGameObject::load(pParams);

  m_callbackID = pParams -> getCallbackID();

  m_currentFrame = MOUSE_OUT;
}

// Draws the menu button.
void MenuButton::draw() {
  SDLGameObject::draw();
}

// Updates the frames of the menu button.
// Takes as parameter the position of the mouse cursor.
void MenuButton::update() {
  engine::Vector2D pMousePos =
  engine::InputHandler::Instance().getMousePosition();

  if (pMousePos.getX() < (m_position.getX() + m_width)
    && pMousePos.getX() > m_position.getX()
    && pMousePos.getY() < (m_position.getY() + m_height)
    && pMousePos.getY() > m_position.getY()) {
    if (engine::InputHandler::Instance().getMouseButtonState(engine::LEFT) &&
     m_bReleased) {
      m_currentFrame = CLICKED;

      m_callback();

      m_bReleased = false;
    } else if (
    !engine::InputHandler::Instance().getMouseButtonState(engine::LEFT)) {
      m_bReleased = true;
      m_currentFrame = MOUSE_OVER;
    }
  } else {
    m_currentFrame = MOUSE_OUT;
  }
}

// Cleans the menu button of the screen.
void MenuButton::clean() {
  SDLGameObject::clean();
}

