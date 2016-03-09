//
//  Enemy.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 8/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "Enemy.h"

Enemy::Enemy(CollisionHandler * col, Vector2f pos, int maxHealth, int maxStrength, float blockWaitTime, float atkPunchCooldown, float atkFootCooldown) : Entity(col, pos, false, maxHealth, maxStrength, blockWaitTime, atkPunchCooldown, atkFootCooldown), targetRange(50)
{
    setMaxVel(Vector2f(.5f, .5f));
    setAccel(Vector2f(.4f, .9f));
    deccel = Vector2f(1, .5f);
}


void Enemy::update(Time time)
{
    Entity::update(time);
    gbHealth.setPosition(getPosition());
}

void Enemy::updateTarget(Entity *target)
{
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
        else if(animationHandler.getType() == WALK)
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
        else if(animationHandler.getType() == WALK)
            setDirection(STOP);

    }

}