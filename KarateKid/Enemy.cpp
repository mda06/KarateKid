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
        if(ex - px < getFighterCharacteristics().getRangeHit() + getGlobalBounds().width)
        {
            //setDirection(STOP);
            setOrientation(LEFT);
            attackPunch();
        }
        else if(ex - px < targetRange + getGlobalBounds().width)
        {
            FloatRect bounds = getGlobalBounds();
            bounds.top += 5;
            bounds.left -= 5;
            if(!colHandler->canMove(bounds))
                setDirection(LEFT);
        }
        else
            setDirection(STOP);
    }
    else if(ex < px)
    {
        if(px - ex < getFighterCharacteristics().getRangeHit() + target->getGlobalBounds().width)
        {
            //setDirection(STOP);
            setOrientation(RIGHT);
            attackPunch();
        }
        else if(px - ex < targetRange + target->getGlobalBounds().width)
        {
            FloatRect bounds = getGlobalBounds();
            bounds.top += 5;
            bounds.left += 5;
            if(!colHandler->canMove(bounds))
                setDirection(RIGHT);
        }
        else
            setDirection(STOP);

    }

}