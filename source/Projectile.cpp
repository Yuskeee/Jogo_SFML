#include "Projectile.h"
#include "Level.h"

using namespace Entities;

Projectile::Projectile(Managers::Graphics* pGraphicsManager, World::Level* pLevel, const sf::Vector2<float>& pos, const sf::Vector2<float>& vel, const bool isPlayers, const bool fromBoss):
Entity(pGraphicsManager, pLevel, pos, vel), Body(pos, vel, {PROJECTILE_WIDTH, PROJECTILE_HEIGHT}), Being(((fromBoss)? boss_projectile:projectile), pos, vel), _isPlayers(isPlayers), _fromBoss(fromBoss){

    velXStart = vel.x;
    velYStart = vel.y;

    if(pGraphicsManager){
        frame = Managers::spriteRect(0, 0, PROJECTILE_WIDTH, PROJECTILE_HEIGHT);
        idTextura = pGraphicsManager->loadTexture(PROJECTILE_TEXTURE_FILE);
        idSprite = pGraphicsManager->createSprite(idTextura);
        pGraphicsManager->setSpriteRect(idSprite, frame);
    }

}

Projectile::Projectile(Managers::Graphics* pGraphicsManager, World::Level* pLevel, const bool fromBoss):
Entity(pGraphicsManager, pLevel), Body(), Being((fromBoss)? boss_projectile:projectile), _isPlayers(), _fromBoss(){
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
    if(velXStart != vel.x || (!_fromBoss && velYStart != vel.y))//se bateu em um bloco, a velocidade foi zerada.
        lives = 0;

    pos += vel*dt;
}

void Projectile::onCollide(Body* other, float dt){
    if((!dynamic_cast<Player*>(other) && _isPlayers) || (dynamic_cast<Player*>(other) && !_isPlayers)){
        lives = 0;
    }
}

const bool Projectile::fromPlayer() const{
    return _isPlayers;
}

void Projectile::saveEntity(std::ofstream& out) const{
    saveEntityInfo(out);
    saveBodyInfo(out);
    out << velXStart  << " " <<
           velYStart  << " " <<
           _isPlayers << " " <<
           _fromBoss  /*<< std::endl*/;

}

void Projectile::loadEntity(std::ifstream& in){
    try{
        loadEntityInfo(in);
        loadBodyInfo(in);

        in >>   velXStart   >>
                velYStart   >>
                _isPlayers  >>
                _fromBoss;
    }
    catch(std::invalid_argument e){
        std::cerr << "Error: could not save Projectile!" << std::endl;
    }
}
