//
//  SmileyManager.cpp
//
//  Created by Cihan Ozer on 08/01/2018.
//

#include "SmileyManager.hpp"

#include "Game.h"

SmileyManager::~SmileyManager()
{
    clear();
}

SmileyManager& SmileyManager::getInstance()
{
    static SmileyManager instance;
    return instance;
}

void SmileyManager::clear()
{
    mSmileyCallbacks.clear();
    mFrameCallbacks.clear();
}

// Call the registered callbacks to let them it is time for the new frame!
void SmileyManager::callOnFrame(const float pDeltaTime)
{
    for(const auto& cb : mFrameCallbacks)
    {
        cb(pDeltaTime);
    }
}

// Add a callback for SmileyEvent handling
void SmileyManager::addSmileyEventCallback(SmileyLogic *const object, void (SmileyLogic::*const func)(SmileyEvent, int))
{
    using namespace std::placeholders;
    mSmileyCallbacks.emplace_back( std::bind(func, object, _1, _2) );
}

// Add a callback for handling the callOnFrame()
void SmileyManager::addFrameCallback(SmileyLogic *const object, void (SmileyLogic::*const func)(const float))
{
    using namespace std::placeholders;
    mFrameCallbacks.emplace_back( std::bind(func, object, _1) );
}

// Request a smiley with the given index from the renderer via the game manager
void SmileyManager::handleSmileyRequest(const int pIndex)
{
    Game::current()->showSmiley(pIndex, false);
}

// Call the registered callbacks to let them SmileyEvent happened
void SmileyManager::callForSmileyEvents(SmileyEvent pEvent, int pIndex)
{
    for(const auto& cb : mSmileyCallbacks)
    {
        cb(pEvent, pIndex);
    }
}
