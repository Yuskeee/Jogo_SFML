#ifndef _RANKING_VIEW_STATE_H
#define _RANKING_VIEW_STATE_H

#include <string>
#include "Ranking.h"

#define MAX_ENTRIES 5

#define DEFAULT_TEXT "0 - VAZIO"

#define RANKING_VIEW_BACKGROUND_FILE "../assets/ground_top.png"

namespace GameSM{

class RankingViewState:public SM::State{

private:

    Managers::Graphics* pGraphicsManager;
    int selection;
    std::string score_nameText;
    Managers::textID titleText;
    Managers::textID positions[MAX_ENTRIES];
    Managers::textID backText;
    Managers::textID eraseText;

    Managers::spriteID background;

    Leaderboard::Ranking *ranking;

private:
    void updateRanking();
    void clear();

public:
    RankingViewState(SM::StateMachine* pStateMachine = NULL, Managers::Graphics* pGraphicsManager = NULL);
    ~RankingViewState();

    virtual void enter(void* arg);
    virtual void exit();

    virtual void update(float dt, Managers::Events* pEventsManager);
    virtual void render(Managers::Graphics* pGraphicsManager);
};
}

#endif
