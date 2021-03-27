#include "Player.h"

#include "Entity.h"

using namespace Entities;

Player::Player(Managers::Graphics* pGraphicsManager, sf::Vector2<float> pos, sf::Vector2<float> vel, sf::Vector2<float> rect, Managers::textureID idT, Managers::spriteID idS):
Entity(pGraphicsManager, pos, vel, rect, idT, idS){

    printf("building PLAYER: %f, %f\n", pos.x, pos.y);

    if(pGraphicsManager){
        idTextura = pGraphicsManager->loadTexture("../assets/green_alien.png");
        idSprite = pGraphicsManager->createSprite(idTextura);
        frame = Managers::spriteRect(0, 0, 16, 20);
        pGraphicsManager->setSpriteRect(idSprite, frame);
    }

}

Player::~Player(){

}

void Player::update(float dt, Managers::Events* pEventsManager){

    if(pEventsManager->keyReleased(Managers::Events::keycode::W))
        vel.y = 0;
    if(pEventsManager->keyReleased(Managers::Events::keycode::D))
        vel.x = 0;
    if(pEventsManager->keyReleased(Managers::Events::keycode::S))
        vel.y = 0;
    if(pEventsManager->keyReleased(Managers::Events::keycode::A))
        vel.x = 0;



    if(pEventsManager->keyDown(Managers::Events::keycode::W)){
        vel.y -= acceleration;
        if(vel.y < -velMax)
            vel.y = -velMax;
    }
            
        
    if(pEventsManager->keyDown(Managers::Events::keycode::D)){
        vel.x += acceleration;
        if(vel.x > velMax)
            vel.x = velMax;
    }
        
    if(pEventsManager->keyDown(Managers::Events::keycode::S)){
        vel.y += acceleration;
        if(vel.y > velMax)
            vel.y = velMax;
    }

    if(pEventsManager->keyDown(Managers::Events::keycode::A)){
        vel.x -= acceleration;
        if(vel.x < -velMax)
            vel.x = -velMax;
    }

    pos += vel*dt;

}

void Player::onCollide(Entity* other){


}