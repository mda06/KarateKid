//
//  Enemy.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 8/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "Enemy.h"

Enemy::Enemy(CollisionHandler * col, Vector2f pos, int maxHealth, int maxStrength, float blockWaitTime, float atkPunchCooldown, float atkFootCooldown, Vector2f size) : Entity(col, pos, size, false, maxHealth, maxStrength, blockWaitTime, atkPunchCooldown, atkFootCooldown, true), targetRange(50)
{
    setMaxVel(Vector2f(250, 250));
    setAccel(Vector2f(200, 450));
    deccel = Vector2f(500, 250);
    
    setOrientation(LEFT);
}


void Enemy::update(Time time)
{
    Vector2f newPos = getPosition();
    if(featureHandler.getSize().y > 48)
        newPos.y -= featureHandler.getSize().y - 48 - 20;
    
    Entity::update(time);
    gbHealth.setPosition(newPos);
}

void Enemy::updateTarget(Entity *target)
{
    if(isEntityUpOrDown(target)) return;
    
    float ex = getPosition().x, px = target->getPosition().x;
    if(ex > px)
    {
        moveLeft(ex, px, target);
    }
    else if(ex < px)
    {
        moveRight(ex, px, target);
    }
}

bool Enemy::isEntityUpOrDown(Entity *target)
{
    float ey = getPosition().y, py = target->getPosition().y;
    if(ey < py)
    {
        if(py - ey > target->getGlobalBounds().height)
            return true;
    }
    else
    {
        if(ey - py > getGlobalBounds().height)
            return true;
    }

    return false;
}

void Enemy::moveLeft(float ex, float px, Entity *target)
{
    FloatRect bounds = getGlobalBounds();
    bounds.left -= getFighterCharacteristics().getRangeHit();
    if(ex - px < getFighterCharacteristics().getRangeHit() + getGlobalBounds().width && getFighterCharacteristics().canAtkPunch())
    {
        setDirection(STOP);
        setOrientation(LEFT);
        attackPunch();
    }
    else if(ex - px < targetRange + getGlobalBounds().width && !colHandler->collisionWithEntity(this, bounds))
    {
        
        FloatRect boundsDown = getGlobalBounds();
        boundsDown.top += 5;
        boundsDown.left -= getFighterCharacteristics().getRangeHit();
        if(colHandler->canMove(bounds) && !colHandler->canMove(boundsDown))
            setDirection(LEFT);
        else
            setDirection(STOP);
    }
    else if(featureHandler.getType() == WALK)
        setDirection(STOP);
}

void Enemy::moveRight(float ex, float px, Entity *target)
{
    FloatRect bounds = getGlobalBounds();
    bounds.left += getFighterCharacteristics().getRangeHit();
    if(px - ex < getFighterCharacteristics().getRangeHit() + target->getGlobalBounds().width && getFighterCharacteristics().canAtkPunch())
    {
        setDirection(STOP);
        setOrientation(RIGHT);
        attackPunch();
    }
    else if(px - ex < targetRange + target->getGlobalBounds().width && !colHandler->collisionWithEntity(this, bounds))
    {
        FloatRect boundsDown = getGlobalBounds();
        boundsDown.top += 5;
        boundsDown.left += getFighterCharacteristics().getRangeHit();;
        if(colHandler->canMove(bounds) && !colHandler->canMove(boundsDown))
            setDirection(RIGHT);
        else
            setDirection(STOP);
    }
    else if(featureHandler.getType() == WALK)
        setDirection(STOP);
}

void Enemy::setTargetRange(int range)
{
    targetRange = range;
}