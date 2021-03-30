#ifndef _PLAYER_H
#define _PLAYER_H

#include "Entity.h"

namespace Entities{

class Player: public Entity{

private:
    const float acceleration = 5;
    const float velMax = 60;
    const float jumpVel = 100;

public:

    Player(Managers::Graphics* pGraphicsManager = NULL, sf::Vector2<float> pos = {0.0f, 0.0f}, sf::Vector2<float> vel = {0.0f, 0.0f}, sf::Vector2<float> rect = {0.0f, 0.0f}, Managers::textureID idT = -1, Managers::spriteID idS = -1);
    virtual ~Player();

    virtual void update(float dt, Managers::Events* pEventsManager);
    virtual void onCollide(Entity* other);


};
}



#endif