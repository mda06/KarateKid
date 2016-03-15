//
//  MenuScreen.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 14/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__MenuScreen__
#define __KarateKid__MenuScreen__

#include "SimpleButton.h"
#include "Screen.h"

class MenuScreen : public AbstractScreen
{
private:
    Window *window;
    SimpleButton btnPlay, btnExit, btnHowTo, btnReturn;
    Texture textHowToPlay, textBG;
    Sprite sprHowToPlay, sprBG;
    bool renderHowToPlay;
    
public:
    MenuScreen(ScreenManager* sm, Window* w);
    void handleInput(Event &event);
    void update(Time time);
    void render(RenderTarget &rt);
};

#endif /* defined(__KarateKid__MenuScreen__) */
