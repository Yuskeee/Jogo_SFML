#ifndef _TREADMILL_H
#define _TREADMILL_H

#include "Entity.h"
#include "Body.h"

namespace Entities{
namespace Obstacles{

#define TREADMILL_WIDTH   48
#define TREADMILL_HEIGHT  6

#define TREADMILL_TEXTURE_FILE   "../assets/treadmill.png"

class Treadmill: public Entity, public Body{

private:

    const float cycleTime = 0.2;
    float cycleTimer;
    const float spinnigSpeed = 80;


public:

    Treadmill(Managers::Graphics* pGraphicsManager = NULL, World::Level* pLevel = NULL, const sf::Vector2<float>& pos = {0.0f, 0.0f});
    virtual ~Treadmill();

    void update(float dt, Managers::Events* pEventsManager);
    void onCollide(Body* other, float dt);

    virtual void saveEntity(std::ofstream& out) const;

};
}
}

#endif