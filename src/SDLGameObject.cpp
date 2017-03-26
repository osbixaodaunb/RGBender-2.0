#include "SDLGameObject.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) : GameObject(pParams), m_position(pParams->getX(), pParams->getY()){
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();

	m_textureID = pParams->getTextureID();

	m_currentRow = 1;
	m_currentFrame = 1;
}

void SDLGameObject::draw(){
	int x = (int) m_position.getX();
	int y = (int) m_position.getY();

	TextureManager::Instance().drawFrame(m_textureID, x, y, m_width, m_height, m_currentRow, m_currentFrame, Game::Instance().getRenderer());
}

void SDLGameObject::update(){

}

void SDLGameObject::clean(){

}
