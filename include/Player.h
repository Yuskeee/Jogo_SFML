#ifndef _PLAYER_H
#define _PLAYER_H

#include "Entity.h"
#include "Body.h"
#include "states/State.h"
#include <iostream>

namespace Entities{

#define DEFAULT   0, 0,  16, 20
#define JUMP     64, 0,  16, 20
#define JUMP_L   80, 0, -16, 20
#define WALK_R1 144, 0,  16, 20
#define WALK_R2 160, 0,  16, 20
#define WALK_L1 160, 0, -16, 20
#define WALK_L2 176, 0, -16, 20

#define WALK_ANIMATION_FRAME_TIME 0.1

#define PLAYER_TEXTURE_FILE   "../assets/green_alien.png"
#define PLAYER2_TEXTURE_FILE  "../assets/blue_alien.png"

class Player: public Entity, public Body{

private:
    enum PlayerStates{
        PlayerJumpStateID,
        PlayerRestStateID,
        //PlayerFireStateID,
        PlayerWalkStateID
    };

    class PlayerJumpState: public SM::State{
    private:
        Player *p;
        bool double_jump;
    public:
        PlayerJumpState(SM::StateMachine* pStateMachine = NULL, Player *p = NULL);
        virtual ~PlayerJumpState();

        void enter(void* arg);

        void update(float dt, Managers::Events* pEventsManager);
        void render(Managers::Graphics* pGraphicsManager);
    };
    class PlayerRestState: public SM::State{
    private:
        Player *p;
    public:
        PlayerRestState(SM::StateMachine* pStateMachine = NULL, Player *p = NULL);
        virtual ~PlayerRestState();

        void enter(void* arg){std::cout << "REST\n";}

        void update(float dt, Managers::Events* pEventsManager);
        void render(Managers::Graphics* pGraphicsManager);
    };
    class PlayerWalkState: public SM::State{
    private:
        Player *p;
        bool nRect;
        float frameTime;
    public:
        PlayerWalkState(SM::StateMachine* pStateMachine = NULL, Player *p = NULL);
        virtual ~PlayerWalkState();

        void enter(void* arg){std::cout << "WALK\n"; nRect = false; frameTime = 0.0f;}

        void update(float dt, Managers::Events* pEventsManager);
        void render(Managers::Graphics* pGraphicsManager);
    };
    /*
    class PlayerFireState: public State{
    };
    */
    class PlayerStateMachine: public SM::StateMachine{
    public:
        PlayerStateMachine(Player *p = NULL);
        virtual ~PlayerStateMachine();
    };

private:
    
    const float groundAcceleration = 9;
    const float airAcceleration = 0.5;
    const float velMax = 100;
    const float jumpVel = 300/*150*/;

    SM::StateMachine *PlayerSM;
    Managers::Graphics* pGraphicsManager;

    Managers::Events::keycode _leftKey;
    Managers::Events::keycode _rightKey;
    Managers::Events::keycode _jumpKey;
    //Managers::Events::keycode _fireKey;

public:

    Player(Managers::Graphics* pGraphicsManager = NULL, const sf::Vector2<float>& pos = {0.0f, 0.0f},
            const sf::Vector2<float>& vel = {0.0f, 0.0f}, const sf::Vector2<float>& rect = {0.0f, 0.0f},
            Managers::textureID idT = -1, Managers::spriteID idS = -1, bool player1 = true);
    virtual ~Player();

    virtual void update(float dt, Managers::Events* pEventsManager);
    virtual void onCollide(Entity* other);

private:

    void loadControl(bool player1);

};
}



#endif
