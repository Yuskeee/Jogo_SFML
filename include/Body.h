#ifndef _BODY_H
#define _BODY_H

#include "Being.h"

class Body: public virtual Being{

protected:

    enum bodyType{
        player_1,
        player_2,
        enemy,
        //inimigo2,
        //projetil,
        nBodyTypes

    };

    int type;

    sf::Vector2<float> rect;
    bool isGrounded;


public:

    Body(bodyType type = player_1, const sf::Vector2<float>& pos = {0.0f, 0.0f}, const sf::Vector2<float>& vel = {0.0f, 0.0f}, const sf::Vector2<float>& rect = {0.0f, 0.0f}, bool isGrounded = false);
    ~Body();

    void onCollide(Body* other);

    void setRect(const sf::Vector2<float>& rect);
    void setGrounded(const bool& isGrounded);

    const sf::Vector2<float> getRect() const;
    const bool getGrounded() const;

};

#endif