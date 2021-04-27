#include "Ghost.h"

using namespace Entities;

Ghost::Ghost(Managers::Graphics* pGraphicsManager, World::Level* pLevel, const sf::Vector2<float>& pos, const sf::Vector2<float>& vel, bool player1):
Entity(pGraphicsManager, pLevel, pos, vel), Being(player1 ? ghost_1:ghost_2, pos, vel){

    this->pGraphicsManager = pGraphicsManager;

    this->pLevel = pLevel;

    loadControl(player1);

    if(pGraphicsManager){
        frame = Managers::spriteRect(0, 0, 16, 20);
        idTextura = pGraphicsManager->loadTexture(player1 ? GHOST1_TEXTURE_FILE : GHOST2_TEXTURE_FILE);
        idSprite = pGraphicsManager->createSprite(idTextura);
        pGraphicsManager->setSpriteRect(idSprite, frame);
    }

}

Ghost::~Ghost(){
}

void Ghost::update(float dt, Managers::Events* pEventsManager){


    if(pEventsManager->keyDown(_rightKey)){
        vel.x += speed;
    }
    if(pEventsManager->keyDown(_downKey)){
        vel.y += speed;
    }
    if(pEventsManager->keyDown(_leftKey)){
        vel.x -= speed;
    }
    if(pEventsManager->keyDown(_upKey)){
        vel.y -= speed;
    }

    pos += vel*dt;

    vel.x = 0;
    vel.y = 0;

}

void Ghost::loadControl(bool player1){
    if(player1){
        _leftKey = Managers::Events::keycode::A;
        _rightKey = Managers::Events::keycode::D;
        _upKey = Managers::Events::keycode::W;
        _downKey = Managers::Events::keycode::S;
    }
    else{
        _leftKey = Managers::Events::keycode::Left;
        _rightKey = Managers::Events::keycode::Right;
        _upKey = Managers::Events::keycode::Up;
        _downKey = Managers::Events::keycode::Down;
    }
}

void Ghost::saveEntity(std::ofstream& out) const{
    saveEntityInfo(out);
    out << std::endl;
}