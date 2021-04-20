#ifndef _SPEARS_H
#define _SPEARS_H

#include "Entity.h"
#include "Body.h"

namespace Entities{
namespace Obstacles{

#define SPEARS_WIDTH   16
#define SPEARS_HEIGHT  20

#define SPEARS_TEXTURE_FILE   "../assets/spears.png"

class Spears: public Entity, public Body{

private:

    const float cycleTime = 2;
    const float flipTime = 0.1;
    float cycleTimer;

    bool active;


public:

    Spears(Managers::Graphics* pGraphicsManager = NULL, World::Level* pLevel = NULL, const sf::Vector2<float>& pos = {0.0f, 0.0f});
    virtual ~Spears();

    void update(float dt, Managers::Events* pEventsManager);
    void onCollide(Body* other, float dt);


};
}
}

#endif