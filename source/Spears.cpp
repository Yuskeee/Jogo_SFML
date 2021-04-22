#include "Spears.h"
#include "Level.h"

using namespace Entities;
using namespace Obstacles;

Spears::Spears(Managers::Graphics* pGraphicsManager, World::Level* pLevel, const sf::Vector2<float>& pos):
Entity(pGraphicsManager, pLevel, pos, {0.0f, 0.0f}), Body(pos, {0.0f, 0.0f}, {SPEARS_WIDTH, SPEARS_HEIGHT}), Being(spears, pos, {0.0f, 0.0f}), startPosX(), startPosY(){

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

    startPosX = this->pos.x;
    startPosY = this->pos.y;
}

Spears::~Spears(){
}

void Spears::update(float dt, Managers::Events* pEventsManager){

    cycleTimer += dt;

    if(cycleTimer > cycleTime - flipTime){
        pos = {startPosX, startPosY};
        frame = Managers::spriteRect(16, 0, SPEARS_WIDTH, SPEARS_HEIGHT);
    }
    if(cycleTimer > cycleTime){
        if(active){
            pos = {startPosX, startPosY + SPEARS_HEIGHT - SPEARS_HEIGHT_DOWN};
            frame = Managers::spriteRect(0, SPEARS_HEIGHT - SPEARS_HEIGHT_DOWN, SPEARS_WIDTH, SPEARS_HEIGHT_DOWN);
        }
        else
            frame = Managers::spriteRect(32, 0, SPEARS_WIDTH, SPEARS_HEIGHT);

        active = !active;

        cycleTimer = 0;
    }

    std::cout << "still here at pos -> x: " << pos.x << ", y: " << pos.y <<std::endl;


}

void Spears::onCollide(Body* other, float dt){
    if(active){
        Entities::Entity* e = NULL;
        e = dynamic_cast<Entities::Entity*>(other);
        if(e)
            e->damage(1);
    }

}
