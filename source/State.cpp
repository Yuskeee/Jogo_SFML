#include "State.h"

//State-------------------------------------------------------
State::State(StateMachine* pStateMachine){
    setStateMachine(pStateMachine);
}

State::~State(){


}

void State::setStateMachine(StateMachine* pStateMachine){
    this->pStateMachine = pStateMachine;
}

StateMachine* State::getStateMachine(){
    return pStateMachine;
}


//StateMachine-------------------------------------------------

StateMachine::StateMachine(){

}

StateMachine::~StateMachine(){

    for(int i = 0; i<states.size(); i++)
        delete states[i];

}

void StateMachine::addState(State* state){
    states.push_back(state);
}

void StateMachine::changeState(stateID nextStateID){
    states[currentStateID]->exit();
    currentStateID = nextStateID;
    states[currentStateID]->enter();

}

void StateMachine::update(float dt, Events* pEvents){
    states[currentStateID]->update(dt, pEvents);
}

void StateMachine::render(Graphics* pGraphics){
    states[currentStateID]->render(pGraphics);
}