/*Copyright 2017 RGBender*/

// Class: ChildBullet.cpp

// Purpose: Handle all necessary actions to create and manipulate a childBullet.

#include "ChildBullet.h"
#include "SDLGameObject.h"
#include "Vector2D.h"
#include "LoaderParams.h"
#include "Timer.h"
#include "Player.h"
#include "Game.h"
#include "InputHandler.h"
#include "Log.h"
#include "Enemy.h"
#include "Physics.h"
#include "GameOverState.h"
#include <iostream>

ChildBullet::~ChildBullet() {
    INFO("REMOVE CHAIR BULLET");
}
//Create the childBullet with 5000 milliseconds to stay in the game
ChildBullet::ChildBullet(Player *target) : SDLGameObject() {
    setPlayer(target);
    timeToLive = 5000; // in milliseconds
    m_active = true;
}
// Load pParams in the game
// Note: the p before every parameters name means parameters
void ChildBullet::load(const engine::LoaderParams* pParams) {
    m_velocity = engine::Vector2D(0, 0);

    SDLGameObject::load(pParams);
}
// Calculates the angle of the childBullet according to the player position
// As a parameter it recive the player position
double ChildBullet::rotateTowards(engine::Vector2D pPosition) {
    engine::Vector2D target = engine::InputHandler::Instance().
                              getMousePosition() - pPosition;
    target = target.norm();

    engine::Vector2D horizontal(0, 1);

    return engine::Vector2D::angle(target, engine::Vector2D(0, 1));
}
// Loads the bullet on game and throws against the player.
// Get as parameters a velocity and a position.
void ChildBullet::load(engine::Vector2D pVelocity, engine::Vector2D pPosition) {
    double angle = rotateTowards(pPosition);

    m_moveSpeed = 8;
    engine::LoaderParams* pParams = new engine::LoaderParams(pPosition.getX(),
                                                             pPosition.getY(),
                                                             42, 42,
                                                             "childBullet", 0,
                                                             0, 0, angle, 35,
                                                             35);
    SDLGameObject::load(pParams);

    m_currentFrame = 0;
    bornTime = engine::Timer::Instance().step();
    m_velocity = pVelocity.norm() * m_moveSpeed;
}

void ChildBullet::draw() {
    SDLGameObject::draw();
}
// Remove the bullet from the game after a certain time period, define by the 
// variable timeToLive, and calls a function to see if the player was hitted
void ChildBullet::update() {
    m_textureID = "childBullet";
    m_position += m_velocity;

    if (engine::Timer::Instance().step() >= bornTime + timeToLive) { // Just verify if the timeToLive has passed
        m_active = false;
       engine::Game::Instance().getStateMachine()->currentState()->
                         removeGameObject(this);
    }

    checkCollision();
}
//Verify if the bullet collided with the player,
//if it has the bullet is removed from the game and 
//the player loses 2 life points, if he was not using a shield.
void ChildBullet::checkCollision() {
    if (m_active) {
        engine::Vector2D pos = m_player->getPosition();
        engine::Vector2D thisPos = getPosition();

        if (engine::Physics::Instance().
            checkCollision(dynamic_cast<SDLGameObject*>(m_player),
                           dynamic_cast<SDLGameObject*>(this))) {
            m_active = false;
           engine::Game::Instance().
                  getStateMachine()->currentState()->removeGameObject(this);
            INFO("Bullet collided");
            INFO("PLAYER LOST THE GAME");
            if (!m_player->getShieldActive())
                m_player->setLife((m_player->getLife()) - 2);
            else if (m_player->getShieldActive())
                m_player->setShieldHits();
        }
    }
}
// Need to be here because childBullet has an inheritance whith SDLGameObejct
void ChildBullet::clean() {
    SDLGameObject::clean();
}

