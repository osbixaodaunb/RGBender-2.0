#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "LoaderParams.h"

#include <SDL2/SDL.h>
#include <string>

class GameObject{
public:
	virtual	void draw()=0;
	virtual void update()=0;
	virtual void clean()=0;

protected:
	GameObject(const LoaderParams* pParams) {}
	virtual ~GameObject() {}
};

#endif
