#include "Flower.h"
#include "Level.h"
#include <math.h>

using namespace Entities;

Flower::Flower(Managers::Graphics* pGraphicsManager, World::Level* pLevel, const sf::Vector2<float>& pos):
Enemy(pGraphicsManager, pLevel, pos, {0.0f, 0.0f}, {FLOWER_WIDTH, FLOWER_HEIGHT}), Being(flower, pos, {0.0f, 0.0f})
{
    attackTimer = 0;

    if(pGraphicsManager){
        frame = Managers::spriteRect(0, 0, 16, 25);
        idTextura = pGraphicsManager->loadTexture(FLOWER_TEXTURE_FILE);
        idSprite = pGraphicsManager->createSprite(idTextura);
        pGraphicsManager->setSpriteRect(idSprite, frame);
    }

}

Flower::~Flower(){


}

void Flower::update(float dt, Managers::Events* pEventsManager){
    attackTimer += dt;

    if(attackTimer >= attackInterval)
        attack();

    if(!vulnerability){
        if(vulnerability_timer > VULNERABILITY_MAX){
            vulnerability = true;
            vulnerability_timer = 0;
        }
        vulnerability_timer += dt;
    }

    pos += vel*dt;
}

void Flower::attack(){
    attackTimer = 0;
    setTarget();

    float distX = target->getPos().x - pos.x;
    float distY = target->getPos().y - pos.y;
    float angle = atan2f(distY, distX);

    Projectile* proj = new Projectile(pLevel->getGraphicsManager(), pLevel, pos, {projectileSpeed*cosf(angle), projectileSpeed*sinf(angle)});

    pLevel->addEntity(static_cast<Entities::Entity*>(proj));
    pLevel->addBody(static_cast<Body*>(proj));


}

void Flower::onCollide(Body* other, float dt){
    if((dynamic_cast<Projectile*>(other) && dynamic_cast<Projectile*>(other)->fromPlayer())){
        lives -= 1;
        if(lives == 0)
            pLevel->setScore(pLevel->getScore() + FLOWER_SCORE_VALUE);
    }
}

void Flower::saveEntity(std::ofstream& out) const{
    saveEntityInfo(out);
    saveBodyInfo(out);
    out <<  attackTimer         << " " <<
            vulnerability_timer /*<< std::endl*/;
}
