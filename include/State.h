#ifndef _STATE_H
#define _STATE_H

#include <vector>
#include "Graphics.h"
#include "Events.h"

typedef int stateID;

class StateMachine;

class State{

protected:
    StateMachine* pStateMachine;// ponteiro para a maquina de estados a qual este estado pertence

public:
    State(StateMachine* pStateMachine = NULL);
    virtual ~State();

    virtual void enter(){}
    virtual void exit(){}

    virtual void update(float dt, Events* pEvents) = 0;
    virtual void render(Graphics* pGraphics) = 0;

    void setStateMachine(StateMachine* pStateMachine);
    StateMachine* getStateMachine();

};

class StateMachine{

protected:
    std::vector<State*> states;
    stateID currentStateID;

public:
    StateMachine();
    virtual ~StateMachine();

    void addState(State* state);
    void changeState(stateID nextStateID);

    void update(float dt, Events* pEvents);
    void render(Graphics* pGraphics);

};


#endif