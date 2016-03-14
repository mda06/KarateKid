//
//  Game.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 29/02/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__Game__
#define __KarateKid__Game__

#include "Scene.h"
#include "MenuScreen.h"

class Game
{
private:
    RenderWindow window;
    Scene scene;
    MenuScreen menuScreen;
    bool renderMenuScreen;
    
public:
    Game();
    void run();
    
};

#endif /* defined(__KarateKid__Game__) */
