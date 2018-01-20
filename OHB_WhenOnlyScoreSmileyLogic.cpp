//
//  OHB_WhenOnlyScoreSmileyLogic.cpp
//
//  Created by Cihan Ozer on 10/01/2018.
//

#include "OHB_WhenOnlyScoreSmileyLogic.hpp"

#include "SmileyScheduler.hpp"

#include "OHB_GameInfo.hpp"

OHB_WhenOnlyScoreSmileyLogic::OHB_WhenOnlyScoreSmileyLogic(SmileyManager* pManager, Agent* pAgent)
    : SmileyLogic(pManager, pAgent)
{
    
}

void OHB_WhenOnlyScoreSmileyLogic::performLogic(const SmileyEvent pEvent, int pIndex)
{
    if(pEvent == SmileyEvent::SCORED_GOAL)
    {
        handleScoreGoal();
    }
    else if(pEvent == SmileyEvent::ANSWER)
    {
        handleAnswerSmiley(pIndex);
    }
}
