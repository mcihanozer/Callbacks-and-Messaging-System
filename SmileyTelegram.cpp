//
//  SmileyTelegram.cpp
//
//  Created by Cihan Ozer on 11/01/2018.
//

#include "SmileyTelegram.hpp"

#include "SmileyLogic.hpp"

SmileyTelegram::SmileyTelegram(
                                const SmileyLogic* pSender,
                                const SmileyEvent pEventType,
                                const int pSmileyId,
                                const float pDelayTime,
                                const ePRIORITY pPriority,
                                const float pValidUntil
                               )
    :   sender(pSender),
        eventType(pEventType),
        mSmileyId(pSmileyId),
        mDelayTime(pDelayTime),
        mSmileyPriority(pPriority),
        mValidUntil(pValidUntil)
{
    mElapsedTime = 0.f;
}

void SmileyTelegram::erase()
{
    sender = NULL;
}

void SmileyTelegram::setSmileyId(const int pId)
{
    mSmileyId = pId;
}

int SmileyTelegram::getSmileyId() const
{
    return mSmileyId;
}

void SmileyTelegram::setDelayTime(const float pDelay)
{
    mDelayTime = pDelay;
}

float SmileyTelegram::getDelayTime() const
{
    return mDelayTime;
}

float SmileyTelegram::getElapsedTime() const
{
    return mElapsedTime;
}

void SmileyTelegram::setValidUntil(const float pValidUntil)
{
    mValidUntil = pValidUntil;
}

float SmileyTelegram::getValidUntil() const
{
    return mValidUntil;
}

bool SmileyTelegram::isStillValid() const
{
    return mElapsedTime < mValidUntil;
}

void SmileyTelegram::setSmileyPriority(const ePRIORITY pPriority)
{
    mSmileyPriority = pPriority;
}

ePRIORITY SmileyTelegram::getSmileyPriority() const
{
    return mSmileyPriority;
}

bool SmileyTelegram::operator==(const SmileyTelegram& t2)
{
    return (
                ( std::fabsf( mDelayTime - t2.getDelayTime() ) < DEFAULT_DELAY_TIME ) &&
                ( mSmileyId == t2.getSmileyId() ) &&
                ( mSmileyPriority == t2.getSmileyPriority() )
            );
}

bool SmileyTelegram::operator<(const SmileyTelegram& t2)
{
    if (*this == t2)
    {
        return false;
    }
    else if( mSmileyPriority == t2.getSmileyPriority() )
    {
        return  ( mDelayTime < t2.getDelayTime() );
    }
    else
    {
        return  ( mSmileyPriority > t2.getSmileyPriority() );
    }
}

void SmileyTelegram::callOnFrame(const float pDetalTime)
{
    mElapsedTime += pDetalTime;
}
