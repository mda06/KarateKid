//
//  GameOverScreen.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 19/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__GameOverScreen__
#define __KarateKid__GameOverScreen__

#include "Screen.h"

class GameOverScreen : public AbstractScreen
{
private:
    Texture txtGameOver;
    Sprite sprGameOver;
    
public:
    GameOverScreen(ScreenManager* sm);
    void handleInput(Event &event);
    void update(Time time);
    void render(RenderTarget &rt);
    
};

#endif /* defined(__KarateKid__GameOverScreen__) */
