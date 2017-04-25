#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "GameObject.h"
#include "GameState.h"

#include <string>
#include <vector>

class PauseState : public GameState{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const {
		return s_pauseID;
	}

	static void s_pauseToMain();
	static void s_resumePlay();
private:

	static const std::string s_pauseID;
};

#endif
