#include "states/State.h"

using namespace SM;
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

void StateMachine::changeState(stateID nextStateID, void* arg){
    states[currentStateID]->exit();
    currentStateID = nextStateID;
    states[currentStateID]->enter(arg);

}

void StateMachine::update(float dt, Managers::Events* pEventsManager){
    states[currentStateID]->update(dt, pEventsManager);
}

void StateMachine::render(Managers::Graphics* pGraphicsManager){
    states[currentStateID]->render(pGraphicsManager);
}

const stateID StateMachine::getCurrentState() const{
    return currentStateID;
}
    
void StateMachine::setCurrentState(const stateID state){
    currentStateID = state;
}