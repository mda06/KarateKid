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

class Scene;
class Entity;

class CollisionHandler
{
private:
    tmx::MapObjects objects;
    Scene *scene;
    
public:
    bool collisionAABB(sf::FloatRect r1, sf::FloatRect r2);
    
public:
    CollisionHandler(Scene *scene);
    void setObjects(tmx::MapObjects obj);
    void handleGameObjects(Entity* e);
    bool canMove(const sf::FloatRect &rect);
    bool collisionWithEntity(Entity* e, sf::FloatRect rect);
    Entity* getCollsionWithEntity(Entity *e, sf::FloatRect rect);
};

#endif /* defined(__KarateKid__CollisionHandler__) */
