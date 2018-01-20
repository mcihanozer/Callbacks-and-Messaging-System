//
//  Created by Cihan Ozer on 08/01/2018.
//

#ifndef SmileyManager_hpp
#define SmileyManager_hpp

#include "AI_Common.hpp"
#include "SmileyLogic.hpp"

#include <vector>

class SmileyManager
{
public:
    
	// SmileyManager is singleton, obviously
    static SmileyManager& getInstance();
    
    void clear();
    
	// The method that is called every frame (i.e. update() in Unity)
    void callOnFrame(const float pDeltaTime);
    
	// Add a SmileyEvent callback
    void addSmileyEventCallback( SmileyLogic* const object, void(SmileyLogic::* const func)(SmileyEvent, int) );
    // Add a callOnFrame() callback
	void addFrameCallback( SmileyLogic* const object, void(SmileyLogic::* const func)(const float) );
    
	// Request a smiley with the given index
    void handleSmileyRequest(const int pIndex);
    
	// Call for the SmileyEvent
    void callForSmileyEvents(SmileyEvent pEvent, int pIndex = -1);
    
private:
    
    SmileyManager() {}
    ~SmileyManager();
    
	// Vector of callbacks for handling SmileyEvent
    std::vector<std::function<void(SmileyEvent, int)>> mSmileyCallbacks;
    
	// Vector of callbacks for handling the new frame
	std::vector<std::function<void(const float)>> mFrameCallbacks;
};

#endif /* SmileyManager_hpp */
