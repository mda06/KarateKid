//
//  FightState.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 5/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "FightState.h"
#include "Entity.h"
#include <iostream>

/*  Abstract
    |
 */
AbstractFightState::AbstractFightState(float active, float cd): activeCooldown(active), cooldown(cd)
{
    curCooldown = 0;
    curActiveCooldown = 0;
}

void AbstractFightState::update(float dt)
{
    curCooldown -= dt;
    curActiveCooldown -= dt;
}

void AbstractFightState::setActiveCooldown(float c)
{
    activeCooldown = c;
    curActiveCooldown = c;
}

void AbstractFightState::setCooldown(float c)
{
    cooldown = c;
    curCooldown = c;
}

bool AbstractFightState::canDoEffect() const
{
    return curCooldown <= 0;
}

bool AbstractFightState::finishEffect() const
{
    return curActiveCooldown <= 0;
}

float AbstractFightState::getActiveCooldown() const
{
    return activeCooldown;
}

float AbstractFightState::getCurActiveCooldown() const
{
    return curActiveCooldown;
}
/*
    |
    Abstract
*/


/*  Normal
    |
*/
FightStateNormal::FightStateNormal() : AbstractFightState(0, 0)
{}

void FightStateNormal::effect(Entity *launcher, Entity *receiver)
{}
/*  |
    Normal
*/



/*  Block
    |
 */
FightStateBlock::FightStateBlock(float maxTime, float waitTime) : AbstractFightState(maxTime, waitTime)
{
    curActiveCooldown = maxTime;
    curCooldown = 0;
}

void FightStateBlock::update(float dt, bool active)
{
    if(active)
    {
        curActiveCooldown -= dt;
    }
    else
    {
        if(curActiveCooldown <= 0)
        {
            if(curCooldown >= cooldown)
            {
                curCooldown = 0;
                curActiveCooldown += dt;
            }
            else
            {
                curCooldown += dt;
            }
        }
        else
        {
            curActiveCooldown += dt / 4;
        }
    }
    
    if(curActiveCooldown < 0) curActiveCooldown = 0;
    if(curActiveCooldown > activeCooldown) curActiveCooldown = activeCooldown;
}

void FightStateBlock::effect(Entity *launcher, Entity *receiver)
{}

bool FightStateBlock::canDoEffect() const
{
    return curCooldown <= 0;
}
/*  |
    Block
 */


/*  ATK
    |
 */
FightStateAttack::FightStateAttack(float act, float cd) : AbstractFightState(act, cd)
{}

void FightStateAttack::effect(Entity *launcher, Entity *receiver)
{
    curCooldown = cooldown;
    curActiveCooldown = activeCooldown;
    if(launcher != NULL && receiver != NULL && !launcher->getFighterCharacteristics().isDead() && !receiver->getFighterCharacteristics().isDead())
    {
        receiver->getFighterCharacteristics().hit(launcher->getFighterCharacteristics().getDamages());
    }
}
/*  |
    ATK
 **/