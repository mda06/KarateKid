//
//  Enemy.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 8/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "Enemy.h"

Enemy::Enemy(CollisionHandler * col, Vector2f pos, int maxHealth, int maxStrength, float blockWaitTime, float atkPunchCooldown, float atkFootCooldown) : Entity(col, pos, false, maxHealth, maxStrength, blockWaitTime, atkPunchCooldown, atkFootCooldown)
{
    
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
        if(ex - px < getFighterCharacteristics().getRangeHit() * 3 + getGlobalBounds().width)
        {
            setOrientation(LEFT);
            attackPunch();
        }
    }
    else if(ex < px)
    {
        if(px - ex < getFighterCharacteristics().getRangeHit() * 3 + target->getGlobalBounds().width)
        {
            setOrientation(RIGHT);
            attackPunch();
        }
    }

}