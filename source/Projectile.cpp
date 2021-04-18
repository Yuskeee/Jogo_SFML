#include "Projectile.h"
#include "Level.h"

using namespace Entities;

Projectile::Projectile(Managers::Graphics* pGraphicsManager, World::Level* pLevel, const sf::Vector2<float>& pos, const sf::Vector2<float>& vel, const bool isPlayers):
Entity(pGraphicsManager, pLevel, pos, vel), Body(pos, vel, {PROJECTILE_WIDTH, PROJECTILE_HEIGHT}), Being(projectile, pos, vel), _isPlayers(isPlayers){

    velXStart = vel.x;
    velYStart = vel.y;

    if(pGraphicsManager){
        frame = Managers::spriteRect(0, 0, PROJECTILE_WIDTH, PROJECTILE_HEIGHT);
        idTextura = pGraphicsManager->loadTexture(PROJECTILE_TEXTURE_FILE);
        idSprite = pGraphicsManager->createSprite(idTextura);
        pGraphicsManager->setSpriteRect(idSprite, frame);
    }

}

Projectile::~Projectile(){
    pGraphicsManager->removeSprite(idSprite);
}

void Projectile::update(float dt, Managers::Events* pEvents){
    if(velXStart != vel.x || velYStart != vel.y)//se bateu em um bloco, a velocidade foi zerada.
        lives = 0;

    pos += vel*dt;
}

void Projectile::onCollide(Body* other){
    if((!dynamic_cast<Player*>(other) && _isPlayers) || (dynamic_cast<Player*>(other) && !_isPlayers)){
        lives = 0;
    }
}

const bool Projectile::fromPlayer() const{
    return _isPlayers;
}