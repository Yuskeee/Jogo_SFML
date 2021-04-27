#ifndef _GHOST_H
#define _GHOST_H

#include "Entity.h"

namespace Entities{

#define GHOST_WIDTH   16.0f
#define GHOST_HEIGHT  20.0f

#define GHOST1_TEXTURE_FILE   "../assets/p1Ghost.png"
#define GHOST2_TEXTURE_FILE  "../assets/p2Ghost.png"    

class Ghost: public Entity{

private:

    const float speed = 90;

    Managers::Events::keycode _leftKey;
    Managers::Events::keycode _rightKey;
    Managers::Events::keycode _upKey;
    Managers::Events::keycode _downKey;


public:

    Ghost(Managers::Graphics* pGraphicsManager = NULL, World::Level* pLevel = NULL, const sf::Vector2<float>& pos = {0.0f, 0.0f}, const sf::Vector2<float>& vel = {0.0f, 0.0f}, bool player1 = true);
    virtual ~Ghost();

    void update(float dt, Managers::Events* pEventsManager);

    virtual void saveEntity(std::ofstream& out) const;

private:

    void loadControl(bool player1);


};
}

#endif