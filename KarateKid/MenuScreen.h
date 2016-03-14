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
#include <SFML/Graphics.hpp>
using namespace sf;

class MenuScreen
{
private:
    Window *window;
    SimpleButton btnPlay, btnExit, btnHowTo, btnReturn;
    Texture textHowToPlay, textBG;
    Sprite sprHowToPlay, sprBG;
    bool renderHowToPlay, play;
    
public:
    MenuScreen(Window* w);
    void handleInput(Event &event);
    void update(float dt);
    void render(RenderTarget &rt);
    void setGoToPlay(bool b);
    bool goToPlay();
};

#endif /* defined(__KarateKid__MenuScreen__) */
