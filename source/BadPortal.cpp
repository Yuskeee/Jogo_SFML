#include "BadPortal.h"
#include "Level.h"

using namespace Entities;

BadPortal::BadPortal(Managers::Graphics* pGraphicsManager, World::Level* pLevel, const sf::Vector2<float>& pos):
Entity(pGraphicsManager, pLevel, pos, {0.0f, 0.0f}), Being(bad_portal, pos, {0.0f, 0.0f}){

    cycleTimer = 0;
    durationTimer = 0;

    this->pGraphicsManager = pGraphicsManager;

    this->pLevel = pLevel;


    if(pGraphicsManager){
        frame = Managers::spriteRect(0, 0, 16, 20);
        idTextura = pGraphicsManager->loadTexture(BAD_PORTAL_TEXTURE_FILE);
        idSprite = pGraphicsManager->createSprite(idTextura);
        pGraphicsManager->setSpriteRect(idSprite, frame);
    }

}

BadPortal::~BadPortal(){
}

void BadPortal::update(float dt, Managers::Events* pEventsManager){

    cycleTimer += dt;
    durationTimer += dt;

    if(cycleTimer > cycleTime){
        frame = Managers::spriteRect(frame.left ? 0 : BAD_PORTAL_WIDTH, 0, BAD_PORTAL_WIDTH, BAD_PORTAL_HEIGHT);
        cycleTimer = 0;
    }
    if(durationTimer > durationTime){
        pLevel->getGenerator()->spawnEnemy(pos);
        lives = 0;
    }

}

void BadPortal::saveEntity(std::ofstream& out) const{
    saveEntityInfo(out);
    out << cycleTimer    << " " <<
           durationTimer /*<< std::endl*/;
}
