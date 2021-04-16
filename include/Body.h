#ifndef _BODY_H
#define _BODY_H

#include "Being.h"

class Body: public virtual Being{

protected:
    const bool gravitableBeingTypes[nBeingTypes] = {
        true,//player1
        true,//player2
        false,//ghost1
        false,//ghost2
        true,//enemy
        false//projectile
    };

    sf::Vector2<float> rect;
    bool isGrounded;


public:

    Body(const sf::Vector2<float>& pos = {0.0f, 0.0f}, const sf::Vector2<float>& vel = {0.0f, 0.0f}, const sf::Vector2<float>& rect = {0.0f, 0.0f}, bool isGrounded = false, beingType type = Being::player_1);
    virtual ~Body();

    virtual void onCollide(Body* other);

    void setRect(const sf::Vector2<float>& rect);
    void setGrounded(const bool& isGrounded);

    const sf::Vector2<float> getRect() const;
    const bool getGrounded() const;
    const bool isGravitable() const;

};

#endif
