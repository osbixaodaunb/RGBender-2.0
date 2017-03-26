#ifndef ENEMY_H
#define ENEMY_H

#include "SDLGameObject.h"
#include "LoaderParams.h"

#include <string>
#include <SDL2/SDL.h>

class Enemy : public SDLGameObject{
public:
	Enemy(const LoaderParams* pParams);

	void draw();
	void update();
	void clean();
};

#endif
