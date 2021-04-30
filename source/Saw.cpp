#include "Saw.h"
#include "Level.h"

using namespace Entities;
using namespace Obstacles;

Saw::Saw(Managers::Graphics* pGraphicsManager, World::Level* pLevel, const sf::Vector2<float>& pos):
Entity(pGraphicsManager, pLevel, pos, {0.0f, 0.0f}), Body(pos, {0.0f, 0.0f}, {SAW_WIDTH, SAW_HEIGHT}), Being(saw, pos, {0.0f, 0.0f}){

    cycleTimer = 0;

    this->pGraphicsManager = pGraphicsManager;

    this->pLevel = pLevel;

    vulnerability = false;

    if(pGraphicsManager){
        frame = Managers::spriteRect(0, 0, SAW_WIDTH, SAW_HEIGHT);
        idTextura = pGraphicsManager->loadTexture(SAW_TEXTURE_FILE);
        idSprite = pGraphicsManager->createSprite(idTextura);
        pGraphicsManager->setSpriteRect(idSprite, frame);
    }

}

Saw::~Saw(){
}

void Saw::update(float dt, Managers::Events* pEventsManager){

    cycleTimer += dt;

    if(cycleTimer > cycleTime){
        frame = Managers::spriteRect(frame.left ? 0 : SAW_WIDTH, 0, SAW_WIDTH, SAW_HEIGHT);
        cycleTimer = 0;
    }

}

void Saw::onCollide(Body* other, float dt){
    Entities::Entity* e = NULL;
        e = dynamic_cast<Entities::Entity*>(other);
        if(e)
            e->damage(1);
}

void Saw::saveEntity(std::ofstream& out) const{
    saveEntityInfo(out);
    saveBodyInfo(out);
    out << cycleTimer /*<< std::endl*/;
}
