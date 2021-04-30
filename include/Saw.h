#ifndef _SAW_H
#define _SAW_H

#include "Entity.h"
#include "Body.h"

namespace Entities{
namespace Obstacles{

#define SAW_WIDTH   16
#define SAW_HEIGHT  8

#define SAW_TEXTURE_FILE   "../assets/saw.png"

class Saw: public Entity, public Body{

private:

    const float cycleTime = 0.05;
    float cycleTimer;


public:

    Saw(Managers::Graphics* pGraphicsManager = NULL, World::Level* pLevel = NULL, const sf::Vector2<float>& pos = {0.0f, 0.0f});
    virtual ~Saw();

    void update(float dt, Managers::Events* pEventsManager);
    void onCollide(Body* other, float dt);

    virtual void saveEntity(std::ofstream& out) const;
    virtual void loadEntity(std::ifstream& in);

};
}
}

#endif
