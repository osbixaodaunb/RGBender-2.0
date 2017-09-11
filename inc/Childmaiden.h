/*Copyright 2017 RGBender*/

// Library: Childmaiden (.h)

// Purpose: This library declares methods that will be used
// later in the Childmaiden.cpp file.

#ifndef INC_CHILDMAIDEN_H_
#define INC_CHILDMAIDEN_H_

#include "SDLGameObject.h"
#include "BaseCreator.h"
#include "Vector2D.h"

// Class constructor method.
class Childmaiden : public engine::SDLGameObject{
 public:
  Childmaiden();
  // Method that load the parameters of the child.
  virtual void load(const engine::LoaderParams* pParams);
  // Method that draws the child.
  virtual void draw();
  // Method that updates child frames.
  virtual void update();
  // Method that cleans the child of the screen.
  virtual void clean();

  // Method that sets visible the child.
  // Receives a boolean to set the visibility.
  void setVisibility(bool visibility) {
    isVisible = visibility;
  }

  // Returns the visibility of the child as true or false.
  bool getVisibility() {
    return isVisible;
  }

 private:
  bool isVisible;
  int sinalx, sinaly;
  int originTime;
  engine::Vector2D startPoint;
};

// Shield creator.
// Returns a new shield of child in the game.
class ChildmaidenCreator : public engine::BaseCreator{
 public:
  engine::GameObject* createGameObject() const{
    return new Childmaiden();
  }
};

#endif  // INC_CHILDMAIDEN_H_
