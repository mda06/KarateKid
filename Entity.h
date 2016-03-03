//
//  Entity.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 29/02/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__Entity__
#define __KarateKid__Entity__

#include "AnimationHandler.h"
#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>
#include "CollisionHandler.h"
using namespace sf;

enum Direction
{
    STOP,
    LEFT,
    RIGHT
};

class Entity
{
private:
    Vector2f vel, maxVel, accel, deccel;
    Direction direction;
    AnimationHandler animationHandler;
    CollisionHandler *colHandler;
    
    void handleMovement(float dt);
    
public:
    Entity(CollisionHandler *col);
    void init();
    void update(Time time);
    void render(RenderTarget &rt);
    Vector2f getPosition() const;
    void setDirection(Direction dir);
    void jump();
    FloatRect getGlobalBounds();
    
};

#endif /* defined(__KarateKid__Entity__) */
