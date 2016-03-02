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

class CollisionHandler
{
private:
    std::vector<tmx::MapObject*> objects;
    
public:
    void setObjects(std::vector<tmx::MapObject*> obj);
    bool canMove(const sf::FloatRect &rect);
};

#endif /* defined(__KarateKid__CollisionHandler__) */
