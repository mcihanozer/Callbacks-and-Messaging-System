//
//  SmileyLogic.cpp
//
//  Created by Cihan Ozer on 08/01/2018.
//

 // OMITTED CODE -Confidential reasons

#include "SmileyLogic.hpp"

#include "SmileyManager.hpp"

#include "SmileyScheduler.hpp"

SmileyLogic::SmileyLogic(SmileyManager* pManager, Agent* pAgent)
{
    pManager->addSmileyEventCallback(this, &SmileyLogic::receiverCallBack);
    pManager->addFrameCallback(this, &SmileyLogic::callOnFrame);

    addNotifierCallback(pManager, &SmileyManager::handleSmileyRequest);

    mAgent = pAgent;
    
    // OMITTED CODE -Confidential reasons
}

SmileyLogic::~SmileyLogic()
{;
    mAgent = NULL;
    
    SmileyManager::getInstance().clear();
    SmileyScheduler::getInstance().clear();
}

// Receives the events from SmileyManager
void SmileyLogic::receiverCallBack(SmileyEvent pEvent, int pIndex)
{
    performLogic(pEvent, pIndex);
}

// Add callback for making smiley requests
void SmileyLogic::addNotifierCallback( SmileyManager* const object, void(SmileyManager::* const func)(const int) )
{
    using namespace std::placeholders;
    mCallbackToNotify = std::bind(func, object, _1);
}

// Makes request to SmileyManager for smiley rendering
void SmileyLogic::notifierCallBack(const int pIndex)
{
    mCallbackToNotify(pIndex);
}

// Is called every frame of the game
void SmileyLogic::callOnFrame(const float pDeltaTime)
{
    performLogic(SmileyEvent::RANDOM, -1);
}

bool SmileyLogic::canSendSmiley(const SmileyEvent pEventType, const ePRIORITY pSmileyPriority) const
{
     // OMITTED CODE -Confidential reasons
    
    return true;
}

bool SmileyLogic::isTimeOkay()
{
    double currentTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    double timeElapsed = currentTime - mLastSmileyTime;

    if(mLastSmileyTime < OHB_EPSILON || timeElapsed > mSmileyWaitLimit )
    {
        return true;
    }
    
    return false;
}

void SmileyLogic::handleGameStart()
{
    if( isTimeOkay() )
    {
        insertSmiley(
                     this, SmileyEvent::START_GAME, handleGameStartSmiley(),
                     0.f, ePRIORITY::eP_MID, (mSmileyWaitLimit - DEFAULT_DELAY_TIME)
                     );
    }
}

void SmileyLogic::handleLostGoal()
{
    float delayTime = 0.f;
    if( !isTimeOkay() )
    {
        delayTime = mSmileyWaitLimit;
    }
    
    insertSmiley(
                    this, SmileyEvent::LOST_GAME, handleLostGoalSmiley(), delayTime,
                    ePRIORITY::eP_MID, (delayTime + (mSmileyWaitLimit - DEFAULT_DELAY_TIME) )
                 );
}

void SmileyLogic::handleScoreGoal()
{
    float delayTime = 0.f;
    if( !isTimeOkay() )
    {
        delayTime = 1.5f;
    }
    
    insertSmiley(
                    this, SmileyEvent::SCORED_GOAL, handleScoreGoalSmiley(), delayTime,
                    ePRIORITY::eP_HIGH, (delayTime + (mSmileyWaitLimit - DEFAULT_DELAY_TIME) )
                 );
}

void SmileyLogic::handleRandomSmileyEvent()
{
    if( isTimeOkay() )
    {
        insertSmiley(
                        this, SmileyEvent::RANDOM, handleRandomSmiley(), 0.f,
                        ePRIORITY::eP_NONE, (mSmileyWaitLimit - DEFAULT_DELAY_TIME)
                     );
    }
}

void SmileyLogic::handleAnswerSmileyEvent(const int pSmileyId)
{
    float delayTime = 0.f;
    if( !isTimeOkay() )
    {
        delayTime = mSmileyWaitLimit;
    }
    
    insertSmiley(
                    this, SmileyEvent::ANSWER, handleAnswerSmiley(pSmileyId), delayTime,
                    ePRIORITY::eP_LOW, (delayTime + (mSmileyWaitLimit - DEFAULT_DELAY_TIME) )
                 );
}

void SmileyLogic::handleGameEnd(const SmileyEvent pEvent)
{
    if( isTimeOkay() )
    {
        ePRIORITY smileyPriority = ePRIORITY::eP_MID;
        if(pEvent == SmileyEvent::WON_GAME)
        {
            smileyPriority = ePRIORITY::eP_HIGH;
        }
        
        insertSmiley(
                        this, pEvent, handleGameEndSmiley(pEvent), 0.f,
                        smileyPriority, (mSmileyWaitLimit - DEFAULT_DELAY_TIME)
                     );
    }
   
}

int SmileyLogic::handleLostGoalSmiley()
{
     // OMITTED CODE -Confidential reasons
    
    return smileyId;
}

int SmileyLogic::handleScoreGoalSmiley()
{
     // OMITTED CODE -Confidential reasons
    
    return smileyId;
}

int SmileyLogic::handleGameStartSmiley()
{
     // OMITTED CODE -Confidential reasons
    
    return smileyId;
}

int SmileyLogic::handleGameEndSmiley(const SmileyEvent pEvent)
{
     // OMITTED CODE -Confidential reasons
    
    return smileyId;
}

int SmileyLogic::handleRandomSmiley()
{
     // OMITTED CODE -Confidential reasons
	 
    return smileyId;
}

int SmileyLogic::handleAnswerSmiley(const int pSmileyId)
{
     // OMITTED CODE -Confidential reasons
	 return smileyId;
}

void SmileyLogic::insertSmiley
(
     const SmileyLogic* pSender,
     const SmileyEvent pEventType,
     const int pSmileyId,
     const float pDelayTime,
     const ePRIORITY pPriority,
     const float pValidUntil
)
{
    mLastSmileyTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    
    SmileyScheduler::getInstance().scheduleSmiley( new SmileyTelegram( this, pEventType, pSmileyId, pDelayTime, pPriority, pValidUntil  )  );
}
