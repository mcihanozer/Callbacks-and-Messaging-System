//
//  SmileyScheduler.cpp
//
//  Created by Cihan Ozer on 11/01/2018.
//

#include "SmileyScheduler.hpp"

#include "SmileyManager.hpp"

SmileyScheduler& SmileyScheduler::getInstance()
{
    static SmileyScheduler instance;
    return instance;
}

SmileyScheduler::~SmileyScheduler()
{
    clear();
}

void SmileyScheduler::clear()
{
    for(auto it = mPriorityQueue.begin(); it != mPriorityQueue.end(); )
    {
        (*it)->erase();
        mPriorityQueue.erase(it++);
    }
    mPriorityQueue.clear();
}

// Schedule a smiley: Add the smiley telegram into the queue
void SmileyScheduler::scheduleSmiley(SmileyTelegram *pSmiley)
{
    pSmiley->setDelayTime( pSmiley->getDelayTime() + DEFAULT_DELAY_TIME );
    mPriorityQueue.insert(pSmiley);
}

// It is called every frame
void SmileyScheduler::callOnFrame(const float pDeltaTime)
{
    checkTelegramList(pDeltaTime);
}

// Make a smiley request to render from SmileyManager
bool SmileyScheduler::requestSmiley(const SmileyTelegram *pSmiley)
{
    if( pSmiley->sender->canSendSmiley( pSmiley->eventType, pSmiley->getSmileyPriority() ) )
    {
        SmileyManager::getInstance().handleSmileyRequest( pSmiley->getSmileyId() );
        return true;
    }
    
    return false;
}


void SmileyScheduler::removeTelegramFromQueue()
{
    if( !mPriorityQueue.empty() )
    {
    
        // TODO handle this better ifpossible. Maybe event-driven again? 
		// The telegram sends an event its iterator and you just remove it
		// instead of iterating through every frame.
		// DOWN-SIDE: You need to add callOnFrame() to the telegrams or still 
		// iterate through them for callOnFrame()
        for(auto it = mPriorityQueue.begin(); it != mPriorityQueue.end(); ) //it++ )
        {
            if( !( (*it)->isStillValid() ) )
            {
                (*it)->erase();
                mPriorityQueue.erase(it++);
            }
            else
            {
                ++it;
            }
        }
    }
}

// It is called every frame by callOnFrame() to make sure the scheduling is handling properly
void SmileyScheduler::checkTelegramList(const float pDeltaTime)
{
    if( !mPriorityQueue.empty() )
    {
        // TODO handle this better ifpossible. Maybe event-driven again? 
		// The part/problem I was talking above
        for(auto it = mPriorityQueue.begin(); it != mPriorityQueue.end(); it++ )
        {
            (*it)->callOnFrame(pDeltaTime);
        }
        
        removeTelegramFromQueue();
        
        if(
                !mPriorityQueue.empty() && ( (*mPriorityQueue.begin())->getElapsedTime() > (*mPriorityQueue.begin())->getDelayTime() )
           )
        {
            if( requestSmiley( (*mPriorityQueue.begin()) ) )
            {
                //remove it from the queue
                mPriorityQueue.erase(mPriorityQueue.begin());
            }
        }
        
    }   // END IF NOT EMPTY
}
