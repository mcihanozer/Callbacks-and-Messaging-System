//
//  SmileyLogic.hpp
//
//  Created by Cihan Ozer on 08/01/2018.
//

#ifndef SmileyLogic_hpp
#define SmileyLogic_hpp

#include "Agent.hpp"

// OMITTED CODE -Confidential reasons

class SmileyManager;

// Base class for smiley logic (characters in a sense)
class SmileyLogic
{
public:

    SmileyLogic(SmileyManager* pManager, Agent* pAgent);
    virtual ~SmileyLogic();
    
	// Add callback for making smiley requests
    void addNotifierCallback( SmileyManager* const object, void(SmileyManager::* const func)(const int) );
    
    // Makes request to SmileyManager for smiley rendering
    void notifierCallBack(const int pIndex);
    
    virtual bool canSendSmiley(const SmileyEvent pEventType, const ePRIORITY pSmileyPriority) const;
    
protected:
    
    // Receives the events from SmileyManager
    void receiverCallBack(SmileyEvent pEvent, int pIndex);
    
    // Smiley logic based on the event
    virtual void performLogic(const SmileyEvent pEvent, int pIndex) = 0;
    
    // Is called every frame of the game
    virtual void callOnFrame(const float pDeltaTime);

    void sentEvent(const SmileyEvent pEvent, int pIndex);
    
    bool isTimeOkay();
    
    // Smiley handling
    virtual void handleLostGoal();
    virtual void handleScoreGoal();
    virtual void handleGameStart();
    virtual void handleRandomSmileyEvent();
    virtual void handleAnswerSmileyEvent(const int pSmileyId);
    virtual void handleGameEnd(const SmileyEvent pEvent);
    
    virtual int handleLostGoalSmiley();
    virtual int handleScoreGoalSmiley();
    virtual int handleGameStartSmiley();
    virtual int handleRandomSmiley();
    virtual int handleAnswerSmiley(const int pSmileyId);
    virtual int handleGameEndSmiley(const SmileyEvent pEvent);
    
    void insertSmiley
    (
         const SmileyLogic* pSender,
         const SmileyEvent pEventType,
         const int pSmileyId = 0,
         const float pDelayTime = 0.f,
         const ePRIORITY pPriority = ePRIORITY::eP_NONE,
         const float pValidUntil = (GAME_START_TIME + 1)
    );
    
    bool mIsPositiveMood;
    
    int mTotalCount;
    
    double mLastSmileyTime, mSmileyWaitLimit;
    
    std::function<void(const int)> mCallbackToNotify;

    Agent* mAgent;
    
};

#endif /* SmileyLogic_hpp */
