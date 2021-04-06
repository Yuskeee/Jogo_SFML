#include "Entity.h"

using namespace Entities;

Entity::Entity(Managers::Graphics* pGraphicsManager, const sf::Vector2<float>& pos, const sf::Vector2<float>& vel, Managers::textureID idT, Managers::spriteID idS):
Being(pos, vel), lives(0), vulnerability(), idTextura(idT), idSprite(idS), frame(0, 0, 0, 0){
}

Entity::~Entity(){
}

void Entity::draw(Managers::Graphics* pGraphicsManager){
    pGraphicsManager->setSpritePos(idSprite, pos.x, pos.y);
    pGraphicsManager->drawSprite(idSprite);
}

