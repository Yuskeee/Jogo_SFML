#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "Entity.h"
#include "Body.h"


namespace Entities{

#define PROJECTILE_WIDTH   10.0f
#define PROJECTILE_HEIGHT  10.0f

#define PROJECTILE_TEXTURE_FILE   "../assets/projec.png"

class Projectile: public Entity, public Body{
private:
    float velXStart, velYStart;
    const bool _isPlayers;

public:
    Projectile(Managers::Graphics* pGraphicsManager = NULL, World::Level* pLevel = NULL, const sf::Vector2<float>& pos = {0.0f, 0.0f}, const sf::Vector2<float>& vel = {0.0f, 0.0f}, const bool isPlayers = false);
    ~Projectile();

    virtual void update(float dt, Managers::Events* pEvents);

    virtual void onCollide(Body* other);

    const bool fromPlayer() const;

};
}

#endif