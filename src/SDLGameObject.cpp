#include "SDLGameObject.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) : GameObject(pParams), m_position(pParams->getX(), pParams->getY()), m_velocity(0,0), m_accelaration(0,0), m_numFrames(pParams->getNumFrames()) {
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();

	m_textureID = pParams->getTextureID();

	m_currentRow = 1;
	m_currentFrame = 1;
}

void SDLGameObject::draw(){
	int x = (int) m_position.getX();
	int y = (int) m_position.getY();

	if(m_velocity.getX() > 0){
		TextureManager::Instance().drawFrame(m_textureID, x, y, m_width, m_height, m_currentRow, m_currentFrame, Game::Instance().getRenderer(), SDL_FLIP_HORIZONTAL);
	} else {
		TextureManager::Instance().drawFrame(m_textureID, x, y, m_width, m_height, m_currentRow, m_currentFrame, Game::Instance().getRenderer());
	}
}

void SDLGameObject::update(){
	m_position += m_velocity;
	m_velocity += m_accelaration;
}

void SDLGameObject::clean(){

}
