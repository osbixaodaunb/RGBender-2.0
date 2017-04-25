#include "AnimatedGraphic.h"
#include "SDLGameObject.h"

#include <iostream>

AnimatedGraphic::AnimatedGraphic(const LoaderParams* pParams, int animSpeed) : SDLGameObject(pParams), m_animSpeed(animSpeed){

}

void AnimatedGraphic::update(){
	SDLGameObject::update();
	m_currentFrame = int(((SDL_GetTicks() / (1000/m_animSpeed)) % m_numFrames));
}

void AnimatedGraphic::draw(){
	SDLGameObject::draw();
}

void AnimatedGraphic::clean(){
	SDLGameObject::update();
}
