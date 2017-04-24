#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "GameObject.h"

#include <string>
#include <vector>

class GameState{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter() = 0;
	virtual bool onExit();

	virtual std::string getStateID() const = 0;

	virtual ~GameState() {}

protected:
	std::vector<GameObject*> m_gameObjects;
};

#endif
