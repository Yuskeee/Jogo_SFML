#include "Treadmill.h"
#include "Level.h"

using namespace Entities;
using namespace Obstacles;

Treadmill::Treadmill(Managers::Graphics* pGraphicsManager, World::Level* pLevel, const sf::Vector2<float>& pos):
Entity(pGraphicsManager, pLevel, pos, {0.0f, 0.0f}), Body(pos, {0.0f, 0.0f}, {TREADMILL_WIDTH, TREADMILL_HEIGHT}), Being(treadmill, pos, {0.0f, 0.0f}){

    cycleTimer = 0;

    this->pGraphicsManager = pGraphicsManager;

    this->pLevel = pLevel;

    vulnerability = false;

    if(pGraphicsManager){
        frame = Managers::spriteRect(0, 0, 48, 6);
        idTextura = pGraphicsManager->loadTexture(TREADMILL_TEXTURE_FILE);
        idSprite = pGraphicsManager->createSprite(idTextura);
        pGraphicsManager->setSpriteRect(idSprite, frame);
    }

}

Treadmill::~Treadmill(){
}

void Treadmill::update(float dt, Managers::Events* pEventsManager){

    cycleTimer += dt;

    if(cycleTimer > cycleTime){
        frame = Managers::spriteRect(0, frame.top ? 0 : TREADMILL_HEIGHT, TREADMILL_WIDTH, TREADMILL_HEIGHT);
        cycleTimer = 0;
    }

}

void Treadmill::onCollide(Body* other, float dt){

    other->setPos({other->getPos().x + spinnigSpeed*dt, pos.y-other->getRect().y});
    other->setVel({other->getVel().x, 0});
    other->setGrounded(true);

}