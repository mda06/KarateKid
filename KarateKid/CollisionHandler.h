//
//  CollisionHandler.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 2/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__CollisionHandler__
#define __KarateKid__CollisionHandler__

#include <vector>
#include <tmx/MapLoader.h>
#include <SFML/Graphics.hpp>

class Game;
class Entity;

class CollisionHandler
{
private:
    tmx::MapObjects objects;
    Game *game;
    bool collisionAABB(sf::FloatRect r1, sf::FloatRect r2);
    
public:
    CollisionHandler(Game *game);
    void setObjects(tmx::MapObjects obj);
    bool canMove(const sf::FloatRect &rect);
    bool collisionWithEntity(Entity* e, sf::FloatRect rect);
};

#endif /* defined(__KarateKid__CollisionHandler__) */
