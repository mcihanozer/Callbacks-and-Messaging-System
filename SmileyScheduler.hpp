//
//  SmileyScheduler.hpp
//
//  Created by Cihan Ozer on 11/01/2018.
//

#ifndef SmileyScheduler_hpp
#define SmileyScheduler_hpp

#include "SmileyTelegram.hpp"

class SmileyScheduler
{
public:
    
    static SmileyScheduler& getInstance();
    
    void clear();
    
    // Schedule a smiley: Add the smiley telegram into the queue
    void scheduleSmiley(SmileyTelegram* pSmiley);
    
    // It is called every frame
    void callOnFrame(const float pDeltaTime);
    
private:
    
    // SmileyScheduler is a singleton class
    SmileyScheduler() {}
    ~SmileyScheduler();
    
    //copy ctor and assignment should be private
    SmileyScheduler(const SmileyScheduler&);
    SmileyScheduler& operator=(const SmileyScheduler&);

    // Make a smiley request to render from SmileyManager
    bool requestSmiley(const SmileyTelegram *pSmiley);
    
    void removeTelegramFromQueue();
    
    // It is called every frame by callOnFrame() to make sure the scheduling
    // is handling properly
    void checkTelegramList(const float pDeltaTime);
    
    // To keep track of the smileys
    std::set<SmileyTelegram*> mPriorityQueue;
    
};

#endif /* SmileyScheduler_hpp */
