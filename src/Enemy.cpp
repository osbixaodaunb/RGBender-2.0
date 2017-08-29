/*Copyright 2017 MIT*/

#include "Enemy.h"
#include "InputHandler.h"
#include "Game.h"
#include "MainMenuState.h"
#include "Log.h"
#include <iostream>
#include <string>
#include "WinGameState.h"

// using namespace std;
// using namespace engine;

Enemy::Enemy() : SDLGameObject() {
    m_totalHealth = 425;
    m_actualHealth = m_totalHealth;
}

void Enemy::load(const engine::LoaderParams* pParams) {
    SDLGameObject::load(pParams);
}

void Enemy::update() {
    m_currentFrame = static_cast<int>(((SDL_GetTicks() / 200) % m_numFrames));
    SDLGameObject::update();
}

void Enemy::clean() {
    SDLGameObject::clean();
}

void Enemy::draw() {
    SDLGameObject::draw();
}

void Enemy::takeDamage(int damage) {
    if (damage >= 0) {
        m_actualHealth -= damage;
        INFO(m_actualHealth);
    } else {
        m_actualHealth = 0;
    }
    INFO("HP ATUAL: ")
    INFO(m_actualHealth);

    changeState();
}

void Enemy::changeState() {
    int halfHealth = m_totalHealth / 2;
    int quarterHealth = m_totalHealth / 4;
    if (m_actualHealth <= halfHealth && m_actualHealth > quarterHealth) {
        if (m_states.size() == 3) {
            m_states.pop_back();
            m_states.back()();  // Executa a funcao half life
        }
    } else if (m_actualHealth <= quarterHealth && m_actualHealth > 0) {
        if (m_states.size() == 2) {
            m_states.pop_back();
            m_states.back()();  // Executa a funcao quarter life
        }
    } else if (m_actualHealth <= 0) {
        INFO("XUXA IS DEAD!");
        engine::TextureManager::Instance().clearFromTextureMap("RAG");
        // Só pra ter um feedback inicial, mas pode remover isso
        engine::Game::Instance().getStateMachine()->
            changeState(new WinGameState());
    }
}
