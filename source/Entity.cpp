#include "Entity.h"

using namespace Entities;

Entity::Entity(Managers::Graphics* pGraphicsManager, const sf::Vector2<float>& pos, const sf::Vector2<float>& vel, Managers::textureID idT, Managers::spriteID idS):
Being(pos, vel), vulnerabilidade(), idTextura(idT), idSprite(idS), frame(0, 0, 0, 0){
    printf("creating entity %f, %f\n", pos.x, pos.y);

}

Entity::~Entity(){
}

void Entity::draw(Managers::Graphics* pGraphicsManager){
    pGraphicsManager->setSpritePos(idSprite, pos.x, pos.y);
    pGraphicsManager->drawSprite(idSprite);
}

