#ifndef _FLOWER_H
#define _FLOWER_H

#include "Enemy.h"
#include "Projectile.h"


namespace Entities{

#define FLOWER_WIDTH   16.0f
#define FLOWER_HEIGHT  25.0f

#define FLOWER_TEXTURE_FILE "../assets/evil_flower.png"

#define FLOWER_SCORE_VALUE 10

class Flower: public Enemy{

private:

    const float attackInterval = 5.0f;
    const float projectileSpeed = 100.0f;
    float attackTimer;

public:
    Flower(Managers::Graphics* pGraphicsManager = NULL, World::Level* pLevel = NULL,
                const sf::Vector2<float>& pos = {0.0f, 0.0f});
    ~Flower();

    virtual void update(float dt, Managers::Events* pEventsManager);
    virtual void attack();

    virtual void onCollide(Body* other);


};

}
#endif