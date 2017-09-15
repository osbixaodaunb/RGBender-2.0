#ifndef WINGAME_STATE_H
#define WINGAME_STATE_H

#include "GameObject.h"
#include "MenuState.h"

#include <string>
#include <vector>

/**
* Win State class header <WinState.h>
* <P> This class consistis in control and manage the Win State of the RGBender
* game
*/

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

#endif
