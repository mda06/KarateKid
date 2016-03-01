//
//  Entity.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 29/02/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "Entity.h"
#include "ResourcePath.hpp"
#include <iostream>

Entity::Entity() : accel(2, 1), deccel(2, 2.f), maxVel(.8f, .9f), jumpMaxCooldown(.5f)
{
    
}

void Entity::init()
{
    direction = STOP;
    pos = Vector2f(50, 16);
    size = Vector2f(48, 48);
    vel = Vector2f();
    texture.loadFromFile(resourcePath() + "blond.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0, 104, 161));
    sprite.setScale(size.x / 104, size.y / 161);
    jumping = STANDING;
    jumpCurCooldown = 0;
}

void Entity::update(float dt)
{
    handleMovement(dt);
}

void Entity::handleMovement(float dt)
{
    if(direction == LEFT) vel.x -= accel.x * dt;
    else if(direction == RIGHT) vel.x += accel.x * dt;
    else
    {
        if(vel.x > 0)
        {
            vel.x -= deccel.x * dt;
            if(vel.x <= 0) vel.x = 0;
        }
        else
        {
            vel.x += deccel.x * dt;
            if(vel.x >= 0) vel.x = 0;
        }
    }
    
    if(vel.x > maxVel.x) vel.x = maxVel.x;
    if(vel.x < -maxVel.x) vel.x = -maxVel.x;
    
    if(jumping == JUMP)
    {
        /*vel.y += accel.y * dt;
        if(vel.y > maxVel.y) vel.y = maxVel.y;
        
        jumpCurCooldown -= dt;
        std::cout << jumpCurCooldown << std::endl;
        if(jumpCurCooldown <= 0) {
            jumping = FALLING;
            jumpCurCooldown = 0;
        }*/
    }
    else if(jumping == FALLING)
    {
        vel.y -= deccel.y * dt;
        if(vel.y < -maxVel.y)
            vel.y = -maxVel.y;
    }
    
    if(vel.y > maxVel.y) vel.y = maxVel.y;
    if(vel.y < -maxVel.y) vel.y = -maxVel.y;
    
    pos += vel;
    if(pos.y < 16) {
        jumping = STANDING;
        vel.y = 0;
        pos.y = 16;
    }
    
    sprite.setPosition(pos.x, 480 - pos.y - size.y);
}

void Entity::render(RenderTarget &rt)
{
    rt.draw(sprite);
}

void Entity::setDirection(Direction dir)
{
    direction = dir;
}

void Entity::jump()
{
    jumping = FALLING;
    vel.y = maxVel.y;
    //jumpCurCooldown = jumpMaxCooldown;
}

Vector2f Entity::getPos() const
{
    return pos;
}