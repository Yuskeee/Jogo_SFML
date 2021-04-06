#ifndef _STATE_H
#define _STATE_H

#include <vector>
#include "Graphics.h"
#include "Events.h"
#include "List.h"

namespace SM{

typedef int stateID;

class StateMachine;

class State{

protected:
    StateMachine* pStateMachine;// ponteiro para a maquina de estados a qual este estado pertence

public:
    State(StateMachine* pStateMachine = NULL);
    virtual ~State();

    virtual void enter(void* arg){}
    virtual void exit(){}

    virtual void update(float dt, Managers::Events* pEventsManager) = 0;
    virtual void render(Managers::Graphics* pGraphicsManager) = 0;

    void setStateMachine(StateMachine* pStateMachine);
    StateMachine* getStateMachine();

};

class StateMachine{

protected:
    List<State*> states;
    stateID currentStateID;

public:
    StateMachine();
    virtual ~StateMachine();

    void addState(State* state);
    void changeState(stateID nextStateID, void* arg);

    void update(float dt, Managers::Events* pEventsManager);
    void render(Managers::Graphics* pGraphicsManager);

};
}

#endif
