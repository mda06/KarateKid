//
//  CollisionHandler.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 2/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "CollisionHandler.h"
#include "Entity.h"
#include <iostream>
#include "Game.h"

CollisionHandler::CollisionHandler(Game *game)
{
    this->game = game;
}

void CollisionHandler::setObjects(tmx::MapObjects obj)
{
    objects = obj;
}

bool CollisionHandler::canMove(const sf::FloatRect& rect)
{
    for(tmx::MapObject mo : objects)
    {
        if(mo.GetAABB().intersects(rect)) {
            return false;
        }
    }
    return true;
}

bool CollisionHandler::collisionWithEntity(Entity *e, FloatRect rect)
{
    for(Entity *ent : game->getEnemies())
    {
        FloatRect r = ent->getGlobalBounds();
        if(collisionAABB(r, rect) && ent != e)
        {
            return true;
        }
    }
    return false;
}

Entity* CollisionHandler::getCollsionWithEntity(Entity *e, FloatRect rect)
{
    for(Entity *ent : game->getEnemies())
    {
        FloatRect r = ent->getGlobalBounds();
        if(collisionAABB(r, rect) && ent != e)
        {
            return ent;
        }
    }
    return NULL;
}

bool CollisionHandler::collisionAABB(FloatRect r1, FloatRect r2)
{
    if(r1.left + r1.width < r2.left
       || r1.left > r2.left + r1.width
       || r1.top + r1.height < r2.top
       || r1.top > r2.top + r2.height
       ) return false;
    
    return true;
}