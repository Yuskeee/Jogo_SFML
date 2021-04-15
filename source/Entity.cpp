#include "Entity.h"

#include "Level.h"

using namespace Entities;

Entity::Entity(Managers::Graphics* pGraphicsManager, World::Level* pLevel, const sf::Vector2<float>& pos, const sf::Vector2<float>& vel):
Being(pos, vel), pGraphicsManager(pGraphicsManager), lives(5), vulnerability(), frame(0, 0, 0, 0){
    this->pLevel = pLevel;
    idSprite = -1;
    idTextura = -1;
}

Entity::~Entity(){
    if(idSprite >= 0)
        pGraphicsManager->removeSprite(idSprite);
}

void Entity::draw(){
    pGraphicsManager->setSpritePos(idSprite, pos.x, pos.y);
    pGraphicsManager->drawSprite(idSprite);
}

int Entity::getLives() const{
    return lives;
}
