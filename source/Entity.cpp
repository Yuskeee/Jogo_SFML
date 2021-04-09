#include "Entity.h"

using namespace Entities;

Entity::Entity(Managers::Graphics* pGraphicsManager, const sf::Vector2<float>& pos, const sf::Vector2<float>& vel, Managers::textureID idT, Managers::spriteID idS):
Being(pos, vel), pGraphicsManager(pGraphicsManager), lives(0), vulnerability(), idTextura(idT), idSprite(idS), frame(0, 0, 0, 0){
}

Entity::~Entity(){
    if(idSprite >= 0)
        pGraphicsManager->removeSprite(idSprite);
}

void Entity::draw(){
    pGraphicsManager->setSpritePos(idSprite, pos.x, pos.y);
    pGraphicsManager->drawSprite(idSprite);
}

