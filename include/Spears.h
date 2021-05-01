#ifndef _SPEARS_H
#define _SPEARS_H

#include "Entity.h"
#include "Body.h"

namespace Entities{
namespace Obstacles{

#define SPEARS_WIDTH   16.0f
#define SPEARS_HEIGHT  20.0f
#define SPEARS_HEIGHT_DOWN 2.0f

#define SPEARS_TEXTURE_FILE   "../assets/spears.png"

class Spears: public Entity, public Body{

private:

    const float cycleTime = 2;
    const float flipTime = 0.1;
    float cycleTimer;

    bool active;
    float startPosX, startPosY;


public:

    Spears(Managers::Graphics* pGraphicsManager = NULL, World::Level* pLevel = NULL, const sf::Vector2<float>& pos = {0.0f, 0.0f});
    virtual ~Spears();

    void update(float dt, Managers::Events* pEventsManager);
    void onCollide(Body* other, float dt);
    virtual void saveEntity(std::ofstream& out) const;
    virtual void loadEntity(std::ifstream& in);

};
}
}

#endif
