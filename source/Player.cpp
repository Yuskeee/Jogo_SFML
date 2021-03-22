#include "Player.h"

#include "Entidade.h"

Player::Player(Graphics* pGraphics, sf::Vector2<float> pos, sf::Vector2<float> vel, sf::Vector2<float> rect, textureID idT, spriteID idS):
Entidade(pGraphics, pos, vel, rect, idT, idS){

    if(pGraphics){
        idTextura = pGraphics->loadTexture("../assets/green_alien.png");
        idSprite = pGraphics->createSprite(idTextura);
        frame = spriteRect(0, 0, 16, 20);
        pGraphics->setSpriteRect(idSprite, frame);
    }

}

Player::~Player(){

}

void Player::update(float dt, Events* pEvents){

    if(pEvents->keyReleased(Events::keycode::W))
        vel.y = 0;
    if(pEvents->keyReleased(Events::keycode::D))
        vel.x = 0;
    if(pEvents->keyReleased(Events::keycode::S))
        vel.y = 0;
    if(pEvents->keyReleased(Events::keycode::A))
        vel.x = 0;



    if(pEvents->keyDown(Events::keycode::W)){
        vel.y -= acceleration;
        if(vel.y < -velMax)
            vel.y = -velMax;
    }
            
        
    if(pEvents->keyDown(Events::keycode::D)){
        vel.x += acceleration;
        if(vel.x > velMax)
            vel.x = velMax;
    }
        
    if(pEvents->keyDown(Events::keycode::S)){
        vel.y += acceleration;
        if(vel.y > velMax)
            vel.y = velMax;
    }

    if(pEvents->keyDown(Events::keycode::A)){
        vel.x -= acceleration;
        if(vel.x < -velMax)
            vel.x = -velMax;
    }

    pos += vel*dt;

}