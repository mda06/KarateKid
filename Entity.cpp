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

Entity::Entity(CollisionHandler *col, Vector2f pos) : accel(2, 1), deccel(1.4f, 2.f), maxVel(.8f, .9f), colHandler(col), initialPos(pos)
{
    
}

void Entity::init()
{
    direction = STOP;
    vel = Vector2f();
    animationHandler.getSprite().setPosition(initialPos);
}

void Entity::update(Time time)
{
    handleMovement(time.asSeconds());
    animationHandler.update(time);
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
    
    vel.y += deccel.y * dt;
    if(vel.y > maxVel.y)
        vel.y = maxVel.y;
    
    Vector2f movement;
    FloatRect bounds = getGlobalBounds();
    bounds.left += vel.x;
    bool colEntity = colHandler->collisionWithEntity(this, bounds);
    if(colHandler->canMove(bounds) && !colEntity)
    {
        movement.x += vel.x;
    }
    else
    {
        vel.x = 0;
        //To climb but not on enemies
        if(!colEntity)
            vel.y -= accel.y * dt * 5;
    }
    
    bounds = getGlobalBounds();
    bounds.top += vel.y;
    if(colHandler->canMove(bounds) && !colHandler->collisionWithEntity(this, bounds))
        movement.y += vel.y;
    else
        vel.y = 0;
    
    animationHandler.move(movement);
}

void Entity::render(RenderTarget &rt)
{
    rt.draw(animationHandler.getSprite());
}

void Entity::setDirection(Direction dir)
{
    direction = dir;
    AnimationType curType = animationHandler.getType();
    switch(dir)
    {
        case STOP : if(curType != IDLE) animationHandler.setType(IDLE); break;
        case LEFT: if(curType != WALK) animationHandler.setType(WALK);
            if(animationHandler.getSprite().getScale().x > 0) animationHandler.getSprite().scale(-1, 1);
            break;
        case RIGHT: if(curType != WALK) animationHandler.setType(WALK);
            if(animationHandler.getSprite().getScale().x < 0) animationHandler.getSprite().scale(-1, 1);
            break;
    }
}

void Entity::jump()
{
    FloatRect bounds = getGlobalBounds();
    bounds.top += 1;
    if(!colHandler->canMove(bounds) || colHandler->collisionWithEntity(this, bounds))
    {
        vel.y = -maxVel.y;
        //animationHandler.setType(JUMP);
    }
}

void Entity::setColor(Color color)
{
    animationHandler.getSprite().setColor(color);
}

void Entity::attackFoot()
{
    animationHandler.setType(ATTACK_FOOT);
}

void Entity::attackPunch()
{
    animationHandler.setType(ATTACK_PUNCH);
}

void Entity::hit()
{
    animationHandler.setType(HIT);
}

void Entity::dead()
{
    animationHandler.setType(DEAD);
}

Vector2f Entity::getPosition() const
{
    return animationHandler.getPosition();
}

FloatRect Entity::getGlobalBounds()
{
    return (animationHandler.getSprite().getGlobalBounds());
}