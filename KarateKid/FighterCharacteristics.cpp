//
//  FighterCharacteristics.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 5/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "FighterCharacteristics.h"
#include "Entity.h"

FighterCharacteristics::FighterCharacteristics(int maxHealth, int maxStrength, float blockWaitTime, float atkPunchCooldown, float atkFootCooldown) : state(NORMAL_STATE), fightBlock(.8f, blockWaitTime), fightAtkPunch(.35f, atkPunchCooldown), fightAtkFoot(.35f, atkFootCooldown), maxHealth(maxHealth), health(maxHealth), rangeHit(10), initStrength(50), maxStrength(maxStrength), currStrength(initStrength), strengthDiff(15), recupStrength(10)
{}

void FighterCharacteristics::init()
{
    health = maxHealth;
    currStrength = initStrength;
}

void FighterCharacteristics::update(float dt)
{
    fightAtkFoot.update(dt);
    fightAtkPunch.update(dt);
    fightBlock.update(dt, state == BLOCK_STATE);
    addStrength(recupStrength * dt);
    
    if(fightAtkFoot.finishEffect() && fightAtkPunch.finishEffect() && fightBlock.finishEffect())
        setFightState(NORMAL_STATE);
}

void FighterCharacteristics::setFightState(FightState fs)
{
    switch(fs)
    {
        case ATTACK_FOOT_STATE : if(!fightAtkFoot.canDoEffect()) return; break;
        case ATTACK_PUNCH_STATE : if(!fightAtkPunch.canDoEffect()) return; addStrength(-strengthDiff); break;
        case BLOCK_STATE : if(!fightBlock.canDoEffect()) return; break;
            
        default: break;
    }
    
    state = fs;
}

void FighterCharacteristics::effect(Entity* launcher, Entity* receiver)
{
    switch(state)
    {
        case ATTACK_FOOT_STATE : fightAtkFoot.effect(launcher, receiver); break;
        case ATTACK_PUNCH_STATE : fightAtkPunch.effect(launcher, receiver); break;
        case BLOCK_STATE : fightBlock.effect(launcher, receiver); break;
        case NORMAL_STATE : fightNormal.effect(launcher, receiver); break;
    }
}

void FighterCharacteristics::hit(int dmg)
{
    float multiplier;
    
    switch (getFightState())
    {
        case NORMAL_STATE: multiplier = 1;
            break;
        case BLOCK_STATE: multiplier = 0.3;
            addStrength(15);
            break;
        case ATTACK_FOOT_STATE:
        case ATTACK_PUNCH_STATE: multiplier = 1.3;
            break;
    }
    
    health -= dmg * multiplier;
    
    if(health < 0) health = 0;
    if(health > maxHealth) health = maxHealth;
}

bool FighterCharacteristics::willKill(int dmg) const
{
    float multiplier;
    
    switch (getFightState())
    {
        case NORMAL_STATE: multiplier = 1;
            break;
        case BLOCK_STATE: multiplier = 0.3;
            break;
        case ATTACK_FOOT_STATE:
        case ATTACK_PUNCH_STATE: multiplier = 1.3;
            break;
    }
    
    if (health <= dmg * multiplier)
        return true;
    else
        return false;
}

void FighterCharacteristics::setHealthAndMaxHealth(int h)
{
    health = maxHealth = h;
}

void FighterCharacteristics::setStrength(int s)
{
    if(s > maxStrength)
        currStrength = maxStrength;
    else if(s<initStrength)
        currStrength = initStrength;
    else
        currStrength = s;
}

void FighterCharacteristics::addMaxStrength(float s)
{
    maxStrength += s;
}

void FighterCharacteristics::addStrength(float s)
{
    if(currStrength + s > maxStrength)
        currStrength = maxStrength;
    else if(currStrength + s < initStrength)
        currStrength = initStrength;
    else
        currStrength += s;
    
    if(currStrength < 0)
        currStrength = 0;
}

void FighterCharacteristics::addHealth(int s)
{
    health += s;
    if(health < 0) health = 0;
    if(health > maxHealth) health = maxHealth;
}

int FighterCharacteristics::getHealth() const
{
    return health;
}

int FighterCharacteristics::getMaxHealth() const
{
    return maxHealth;
}

int FighterCharacteristics::getRangeHit() const
{
    return rangeHit;
}

int FighterCharacteristics::getCurrStrength() const
{
    return currStrength;
}

int FighterCharacteristics::getMaxStrength() const
{
    return maxStrength;
}

int FighterCharacteristics::getStrengthDiff() const
{
    return strengthDiff;
}

int FighterCharacteristics::getDamages() const
{
    return currStrength * 2;
}

bool FighterCharacteristics::canAtkFoot() const
{
    return fightAtkFoot.canDoEffect();
}

bool FighterCharacteristics::isDead() const
{
    return health <= 0;
}

FightState FighterCharacteristics::getFightState() const
{
    return state;
}

FightStateAttack &FighterCharacteristics::getAtkFootState()
{
    return fightAtkFoot;
}

FightStateAttack &FighterCharacteristics::getAtkPunchState()
{
    return fightAtkPunch;
}

FightStateBlock &FighterCharacteristics::getBlockState()
{
    return fightBlock;
}

bool FighterCharacteristics::canAtkPunch() const
{
    return fightAtkPunch.canDoEffect();
}

bool FighterCharacteristics::canBlock() const
{
    return fightBlock.canDoEffect();
}