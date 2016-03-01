//
//  Game.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 29/02/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__Game__
#define __KarateKid__Game__

#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>
#include "Entity.h"

using namespace sf;
using namespace tmx;

class Game
{
private:
    void init();
    void handleInput();
    void update(float dt);
    void render();
    RenderWindow window;
    Event event;
    MapLoader ml;
    View mapView;
    Entity player;
    
public:
    Game();
    void run();
    
};

#endif /* defined(__KarateKid__Game__) */
