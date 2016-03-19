//
//  Enemy.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 8/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "Enemy.h"

Enemy::Enemy(CollisionHandler * col, Vector2f pos, int maxHealth, int maxStrength, float blockWaitTime, float atkPunchCooldown, float atkFootCooldown, Vector2f size) : Entity(col, pos, size, false, maxHealth, maxStrength, blockWaitTime, atkPunchCooldown, atkFootCooldown), targetRange(50)
{
    
    setMaxVel(Vector2f(250, 250));
    setAccel(Vector2f(200, 450));
    deccel = Vector2f(500, 250);
}


void Enemy::update(Time time)
{
    Entity::update(time);
    gbHealth.setPosition(getPosition());
}

void Enemy::updateTarget(Entity *target)
{
    float ey = getPosition().y, py = target->getPosition().y;
    if(ey < py)
    {
        if(py - ey > target->getGlobalBounds().height)
            return;
    }
    else
    {
        if(ey - py > getGlobalBounds().height)
            return;
    }
    
    float ex = getPosition().x, px = target->getPosition().x;
    if(ex > px)
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
    else if(ex < px)
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

}