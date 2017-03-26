#include "Enemy.h"

#include <string>

using namespace std;

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams){

}

void Enemy::update(){
	m_position += Vector2D(1, 1).norm();
	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

void Enemy::clean(){
	
}

void Enemy::draw(){
	SDLGameObject::draw();
}
