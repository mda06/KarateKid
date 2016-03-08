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
#include <string>
#include <vector>
#include "CollisionHandler.h"
#include "Enemy.h"
#include "Player.h"

using namespace sf;
using namespace tmx;

class Game
{
private:
    void init();
    void initEnemies();
    void handleInput();
    void update(Time time);
    void updateView();
    void render();
    void printFloatRect(const FloatRect &r);
    RenderWindow window;
    Event event;
    MapLoader ml;
    View mapView, hudView;
    Player *player;
    CollisionHandler *colHandler;
    std::string filePath;
    std::vector<Enemy*> enemies;
    Font font;
    Text txtPosition;
    Keyboard::Key keyBlock;
    
public:
    Game();
    ~Game();
    void run();
    std::vector<Enemy*> getEnemies();
    Player* getPlayer();
    
};

#endif /* defined(__KarateKid__Game__) */
