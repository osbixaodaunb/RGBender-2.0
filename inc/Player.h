#ifndef PLAYER_H
#define PLAYER_H

#include "SDLGameObject.h"
#include "LoaderParams.h"

#include <string>
#include <SDL2/SDL.h>

class Player : public SDLGameObject{
public:
	Player(const LoaderParams* pParams);

	void draw();
	void update();
	void clean();

};

#endif
