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
	m_x -= 1;
	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));

}

void Player::clean(){

}
