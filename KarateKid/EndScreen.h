//
//  EndScreen.h
//  KarateKid
//
//  Created by Timothy Van Peteghem on 28/03/16.
//  Copyright © 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef EndScreen_h
#define EndScreen_h

#include "Screen.h"

class EndScreen : public AbstractScreen
{
private:
    Texture txtEnd;
    Sprite sprEnd;
    
public:
    EndScreen(ScreenManager* sm);
    void handleInput(Event &event);
    void update(Time time);
    void render(RenderTarget &rt);
};

#endif /* EndScreen_h */
