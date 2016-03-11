//
//  CollisionHandler.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 2/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "CollisionHandler.h"
#include "GameObject.h"
#include "Entity.h"
#include <iostream>
#include "Game.h"

CollisionHandler::CollisionHandler(Scene *scene)
{
    this->scene = scene;
}

void CollisionHandler::setObjects(tmx::MapObjects obj)
{
    objects = obj;
}

void CollisionHandler::handleGameObjects(Entity *e)
{
    for(GameObject* go : scene->getGameObjects())
    {
        if(collisionAABB(go->getBounds(), e->getGlobalBounds()))
            go->effect(e);
    }
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
    for(Enemy *ent : scene->getEnemies())
    {
        FloatRect r = ent->getGlobalBounds();
        if(collisionAABB(r, rect) && ent != e && !ent->getFighterCharacteristics().isDead())
        {
            return true;
        }
    }
    
    if(collisionAABB(scene->getPlayer()->getGlobalBounds(), rect) && scene->getPlayer() != e && !scene->getPlayer()->getFighterCharacteristics().isDead())
        return true;
    
    return false;
}

Entity* CollisionHandler::getCollsionWithEntity(Entity *e, FloatRect rect)
{
    for(Enemy *ent : scene->getEnemies())
    {
        FloatRect r = ent->getGlobalBounds();
        if(collisionAABB(r, rect) && ent != e && !ent->getFighterCharacteristics().isDead())
        {
            return ent;
        }
    }
    
    if(collisionAABB(scene->getPlayer()->getGlobalBounds(), rect) && scene->getPlayer() != e && !scene->getPlayer()->getFighterCharacteristics().isDead())
        return scene->getPlayer();
    
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