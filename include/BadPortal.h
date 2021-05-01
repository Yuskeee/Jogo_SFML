#ifndef _BAD_PORTAL_H
#define _BAD_PORTAL_H

#include "Entity.h"

namespace Entities{

#define BAD_PORTAL_WIDTH   16.0f
#define BAD_PORTAL_HEIGHT  20.0f

#define BAD_PORTAL_TEXTURE_FILE   "../assets/bad_portal.png"

class BadPortal: public Entity{

private:

    const float cycleTime = 0.2;
    float cycleTimer;

    const float durationTime = 2;
    float durationTimer;

public:

    BadPortal(Managers::Graphics* pGraphicsManager = NULL, World::Level* pLevel = NULL, const sf::Vector2<float>& pos = {0.0f, 0.0f});
    virtual ~BadPortal();

    void update(float dt, Managers::Events* pEventsManager);

    virtual void saveEntity(std::ofstream& out) const;
    virtual void loadEntity(std::ifstream& in);

};
}

#endif
