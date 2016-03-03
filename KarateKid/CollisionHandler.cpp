//
//  CollisionHandler.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 2/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "CollisionHandler.h"
#include <iostream>

void CollisionHandler::setObjects(std::vector<tmx::MapObject*> obj)
{
    objects = obj;
}

bool CollisionHandler::canMove(const sf::FloatRect& rect)
{
    for(tmx::MapObject* mo : objects)
    {
        if(mo->GetAABB().intersects(rect)) {
            return false;
        }
    }
    return true;
}