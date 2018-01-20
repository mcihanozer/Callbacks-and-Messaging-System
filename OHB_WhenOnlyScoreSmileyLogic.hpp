//
//  OHB_WhenOnlyScoreSmileyLogic.hpp
//
//  Created by Cihan Ozer on 10/01/2018.
//

#ifndef OHB_WhenOnlyScoreSmileyLogic_hpp
#define OHB_WhenOnlyScoreSmileyLogic_hpp

#include "SmileyLogic.hpp"

// Example usage
class OHB_WhenOnlyScoreSmileyLogic : public SmileyLogic
{
public:
    
    OHB_WhenOnlyScoreSmileyLogic(SmileyManager* pManager, Agent* pAgent);
    virtual ~OHB_WhenOnlyScoreSmileyLogic() { }
    
protected:
    
    virtual void performLogic(const SmileyEvent pEvent, int pIndex);
};

#endif /* OHB_WhenOnlyScoreSmileyLogic_hpp */
