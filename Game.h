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
#include "CollisionHandler.h"
#include "Entity.h"

using namespace sf;
using namespace tmx;

class Game
{
private:
    void init();
    void handleInput();
    void update(Time time);
    void updateColHandler();
    void render();
    void printFloatRect(const FloatRect &r);
    RenderWindow window;
    Event event;
    MapLoader ml;
    View mapView;
    Entity *player;
    CollisionHandler *colHandler;
    
public:
    Game();
    ~Game();
    void run();
    
};

#endif /* defined(__KarateKid__Game__) */
