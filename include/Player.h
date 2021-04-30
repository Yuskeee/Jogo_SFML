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

#define PLAYER_WIDTH   16.0f
#define PLAYER_HEIGHT  20.0f

#define PLAYER_TEXTURE_FILE   "../assets/green_alien.png"
#define PLAYER2_TEXTURE_FILE  "../assets/blue_alien.png"

#define VULNERABILITY_MAX 0.5f

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
    public:
        PlayerWalkState(SM::StateMachine* pStateMachine = NULL, Player *p = NULL);
        virtual ~PlayerWalkState();

        void enter(void* arg){std::cout << "WALK\n"; p->nRect = false; p->frameTime = 0.0f;}

        void update(float dt, Managers::Events* pEventsManager);
        void render(Managers::Graphics* pGraphicsManager);
    };
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
    World::Level* pLevel;

    Managers::Events::keycode _leftKey;
    Managers::Events::keycode _rightKey;
    Managers::Events::keycode _jumpKey;
    Managers::Events::keycode _fireKey;

    bool rightDirection;
    bool double_jump;
    bool nRect;

    float frameTime;

    float vulnerability_timer;

    const float attackInterval = 0.5f;
    const float projectileSpeed = 300.0f;
    float attackTimer;

public:

    Player(Managers::Graphics* pGraphicsManager = NULL, World::Level* pLevel = NULL, const sf::Vector2<float>& pos = {0.0f, 0.0f}, const sf::Vector2<float>& vel = {0.0f, 0.0f}, const bool player1 = true);
    Player(const bool player1);
    virtual ~Player();

    void update(float dt, Managers::Events* pEventsManager);
    void onCollide(Body* other, float dt) override;

    void saveEntity(std::ofstream& out) const;
    void loadEntity(std::ifstream& in);

private:

    void loadControl(bool player1);

};

}

#endif
