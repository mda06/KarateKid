//
//  WinScreen.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 19/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__WinScreen__
#define __KarateKid__WinScreen__

#include "Screen.h"

class WinScreen : public AbstractScreen
{
private:
    Texture txtWin;
    Sprite sprWin;
    
public:
    WinScreen(ScreenManager* sm);
    void handleInput(Event &event);
    void update(Time time);
    void render(RenderTarget &rt);
};


#endif /* defined(__KarateKid__WinScreen__) */
