//
//  Screen.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 15/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__Screen__
#define __KarateKid__Screen__

#include <SFML/Graphics.hpp>
using namespace sf;

class ScreenManager;

class AbstractScreen
{
protected:
    ScreenManager* screenManager;
    
public:
    AbstractScreen(ScreenManager *sm);
    virtual ~AbstractScreen();
    virtual void handleInput(Event &event) = 0;
    virtual void update(Time time) = 0;
    virtual void render(RenderTarget &rt) = 0;
    virtual void enter();
    virtual void leave();
};

#endif /* defined(__KarateKid__Screen__) */
