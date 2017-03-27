#include "Player.h"
#include "SDLGameObject.h"
#include "LoaderParams.h"

#include <string>
#include <SDL2/SDL.h>

using namespace std;

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams){

}

void Player::draw(){
	SDLGameObject::draw();
}

void Player::update(){
	m_accelaration = Vector2D(0.01, 0);
	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));

	SDLGameObject::update();
}

void Player::clean(){

}
