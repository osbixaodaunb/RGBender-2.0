#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H

#include "GameObject.h"
#include "LoaderParams.h"
#include "TextureManager.h"

#include <string>

class SDLGameObject : public GameObject{
public:
	SDLGameObject(const LoaderParams* pParams);

	virtual void draw();
	virtual void update();
	virtual void clean();

protected:

	int m_x;
	int m_y;

	int m_width;
	int m_height;

	int m_currentFrame;
	int m_currentRow;

	std::string m_textureID;

};

#endif
