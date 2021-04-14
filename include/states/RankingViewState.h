#ifndef _RANKING_VIEW_STATE_H
#define _RANKING_VIEW_STATE_H

#include <string>
//#include "Ranking.h"

#define MAX_ENTRIES 5

namespace GameSM{

class RankingViewState:public SM::State{

private:

    int selection;
    std::string score_nameText;
    Managers::textID titleText;
    Managers::textID positions[MAX_ENTRIES];
    Managers::textID backText;
    Managers::textID eraseText;

    //Ranking ranking;

public:
    RankingViewState(SM::StateMachine* pStateMachine = NULL, Managers::Graphics* pGraphicsManager = NULL);
    ~RankingViewState();

    virtual void update(float dt, Managers::Events* pEventsManager);
    virtual void render(Managers::Graphics* pGraphicsManager);
};
}

#endif
