#ifndef _BODY_H
#define _BODY_H

#include "Being.h"

#include <iostream>

class Body: public virtual Being{

protected:
    const bool gravitableBeingTypes[nBeingTypes] = {
        true,//player1
        true,//player2
        false,//ghost1
        false,//ghost2
        false,//good_portal
        false,//bad_portal
        true,//zombie
        true,//flower
        true,//boss
        false,//projectile
        false,//treadmill
        false,//spears
        false,//saw
        true//boss_projectile
    };

    sf::Vector2<float> rect;
    bool isGrounded;


public:

    Body(const sf::Vector2<float>& pos = {0.0f, 0.0f}, const sf::Vector2<float>& vel = {0.0f, 0.0f}, const sf::Vector2<float>& rect = {0.0f, 0.0f}, bool isGrounded = false, beingType type = Being::player_1);
    virtual ~Body();

    virtual void onCollide(Body* other, float dt);

    void setRect(const sf::Vector2<float>& rect);
    void setGrounded(const bool& isGrounded);

    const sf::Vector2<float> getRect() const;
    const bool getGrounded() const;
    const bool isGravitable() const;

    void saveBodyInfo(std::ofstream& out) const;
    const bool loadBodyInfo(std::ifstream& in);

};

#endif
