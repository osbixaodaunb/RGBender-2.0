/*Copyright 2017 MIT*/
#include "MenuButton.h"
#include "Vector2D.h"
#include "InputHandler.h"

// using namespace engine;

MenuButton::MenuButton() : SDLGameObject() {
}

void MenuButton::load(const engine::LoaderParams* pParams) {
  SDLGameObject::load(pParams);

  m_callbackID = pParams -> getCallbackID();

  m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw() {
  SDLGameObject::draw();
}

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

void MenuButton::clean() {
  SDLGameObject::clean();
}

