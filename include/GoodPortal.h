#ifndef _GOOD_PORTAL_H
#define _GOOD_PORTAL_H

#include "Entity.h"
#include "Body.h"

namespace Entities{

#define GOOD_PORTAL_WIDTH   16.0f
#define GOOD_PORTAL_HEIGHT  20.0f

#define GOOD_PORTAL_TEXTURE_FILE   "../assets/good_portal.png"

class GoodPortal: public Entity, public Body{

private:

    const float cycleTime = 0.2;
    float cycleTimer;

    const float durationTime = 2;
    float durationTimer;

public:

    GoodPortal(Managers::Graphics* pGraphicsManager = NULL, World::Level* pLevel = NULL, const sf::Vector2<float>& pos = {0.0f, 0.0f});
    virtual ~GoodPortal();

    void update(float dt, Managers::Events* pEventsManager);
    void onCollide(Body* other);


};
}

#endif