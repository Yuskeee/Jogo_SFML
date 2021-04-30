#include "GoodPortal.h"
#include "Level.h"

using namespace Entities;

GoodPortal::GoodPortal(Managers::Graphics* pGraphicsManager, World::Level* pLevel, const sf::Vector2<float>& pos):
Entity(pGraphicsManager, pLevel, pos, {0.0f, 0.0f}), Body(pos, {0.0f, 0.0f}, {GOOD_PORTAL_WIDTH, GOOD_PORTAL_HEIGHT}), Being(good_portal, pos, {0.0f, 0.0f}){

    cycleTimer = 0;

    this->pGraphicsManager = pGraphicsManager;

    this->pLevel = pLevel;


    if(pGraphicsManager){
        frame = Managers::spriteRect(0, 0, 16, 20);
        idTextura = pGraphicsManager->loadTexture(GOOD_PORTAL_TEXTURE_FILE);
        idSprite = pGraphicsManager->createSprite(idTextura);
        pGraphicsManager->setSpriteRect(idSprite, frame);
    }

}

GoodPortal::~GoodPortal(){
}

void GoodPortal::update(float dt, Managers::Events* pEventsManager){

    cycleTimer += dt;

    if(cycleTimer > cycleTime){
        frame = Managers::spriteRect(frame.left ? 0 : GOOD_PORTAL_WIDTH, 0, GOOD_PORTAL_WIDTH, GOOD_PORTAL_HEIGHT);
        cycleTimer = 0;
    }

}

void GoodPortal::onCollide(Body* other, float dt){

    if(dynamic_cast<Player*>(other))
        pLevel->requestLevelChange();//notifica a fase que uma mudanca é esperada, mas nao muda agora pois o processamento das entidades ainda esta em curso

}

void GoodPortal::saveEntity(std::ofstream& out) const{
    saveEntityInfo(out);
    saveBodyInfo(out);
    out << cycleTimer /*<< std::endl*/;

}
