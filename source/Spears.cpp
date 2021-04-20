#include "Spears.h"
#include "Level.h"

using namespace Entities;
using namespace Obstacles;

Spears::Spears(Managers::Graphics* pGraphicsManager, World::Level* pLevel, const sf::Vector2<float>& pos):
Entity(pGraphicsManager, pLevel, pos, {0.0f, 0.0f}), Body(pos, {0.0f, 0.0f}, {SPEARS_WIDTH, SPEARS_HEIGHT}), Being(spears, pos, {0.0f, 0.0f}){

    cycleTimer = 0;

    active = false;

    this->pGraphicsManager = pGraphicsManager;

    this->pLevel = pLevel;


    if(pGraphicsManager){
        frame = Managers::spriteRect(0, 0, SPEARS_WIDTH, SPEARS_HEIGHT);
        idTextura = pGraphicsManager->loadTexture(SPEARS_TEXTURE_FILE);
        idSprite = pGraphicsManager->createSprite(idTextura);
        pGraphicsManager->setSpriteRect(idSprite, frame);
    }

}

Spears::~Spears(){
}

void Spears::update(float dt, Managers::Events* pEventsManager){

    cycleTimer += dt;

    if(cycleTimer > cycleTime - flipTime){
        frame = Managers::spriteRect(16, 0, SPEARS_WIDTH, SPEARS_HEIGHT);
    }
    if(cycleTimer > cycleTime){
        if(active)
            frame = Managers::spriteRect(0, 0, SPEARS_WIDTH, SPEARS_HEIGHT);
        else
            frame = Managers::spriteRect(32, 0, SPEARS_WIDTH, SPEARS_HEIGHT);

        active = !active;

        cycleTimer = 0;
    }


}

void Spears::onCollide(Body* other, float dt){
    if(active){
        Entities::Entity* e = NULL;
        e = dynamic_cast<Entities::Entity*>(other);
        if(e)
            e->damage(1);
    }

}