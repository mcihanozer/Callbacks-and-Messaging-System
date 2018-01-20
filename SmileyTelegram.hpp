//
//  SmileyTelegram.hpp
//
//  Created by Cihan Ozer on 11/01/2018.
//

#ifndef SmileyTelegram_hpp
#define SmileyTelegram_hpp

#include "AI_Common.hpp"

class SmileyLogic;

class SmileyTelegram
{
public:
    
    SmileyTelegram(
                    const SmileyLogic* pSender,
                    const SmileyEvent pEventType,
                    const int pSmileyId = 0,
                    const float pDelayTime = 0.f,
                    const ePRIORITY pPriority = ePRIORITY::eP_NONE,
                    const float pValidUntil = (GAME_START_TIME + 1)
                   );
    
    ~SmileyTelegram()
    {
        erase();
    }
    
    void erase();
    
    void setSmileyId(const int pId);
    int getSmileyId() const;
    
    void setDelayTime(const float pDelay);
    float getDelayTime() const;
    float getElapsedTime() const;
    
    void setValidUntil(const float pValidUntil);
    float getValidUntil() const;
    bool isStillValid() const;
    
    void setSmileyPriority(const ePRIORITY pPriority);
    ePRIORITY getSmileyPriority() const;
    
    bool operator==(const SmileyTelegram& t2);
    bool operator<(const SmileyTelegram& t2);
    
    void callOnFrame(const float pDetalTime);
    
    const SmileyLogic* sender;
    SmileyEvent eventType;
    
private:
    
    int mSmileyId;
    
    float mElapsedTime, mDelayTime;
    float mValidUntil;
    
    ePRIORITY mSmileyPriority;
};

#endif /* SmileyTelegram_hpp */
