#ifndef GAMEOVER_STATE_H
#define GAMEOVER_STATE_H

#include "GameState.h"

#include <string>

class GameOverState : public GameState{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const {
		return s_gameOverID;
	}

private:
	static void s_gameOverToMain();
	static void s_restartPlay();

	static const std::string s_gameOverID;
};

#endif
