//
//  FighterCharacteristics.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 5/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "FighterCharacteristics.h"
#include "Entity.h"

FighterCharacteristics::FighterCharacteristics() : state(NORMAL_STATE), fightBlock(.2f), fightAtkPunch(.35f), fightAtkFoot(.35f), maxHealth(1000), health(maxHealth), rangeHit(10), strength(100)
{}

void FighterCharacteristics::init()
{
    health = maxHealth;
}

void FighterCharacteristics::update(float dt)
{
    fightAtkFoot.update(dt);
    fightAtkPunch.update(dt);
    fightBlock.update(dt);
    
    if(fightAtkFoot.finishEffect() && fightAtkPunch.finishEffect() && fightBlock.finishEffect())
        setFightState(NORMAL_STATE);
}

void FighterCharacteristics::setFightState(FightState fs)
{
    switch(fs)
    {
        case ATTACK_FOOT_STATE : if(!fightAtkFoot.canDoEffect()) return;
        case ATTACK_PUNCH_STATE : if(!fightAtkPunch.canDoEffect()) return;
        case BLOCK_STATE : if(!fightBlock.canDoEffect()) return;
            
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
    health -= dmg;
    if(health < 0) health = 0;
    if(health > maxHealth) health = maxHealth;
}

void FighterCharacteristics::setHealthAndMaxHealth(int h)
{
    health = maxHealth = h;
}

void FighterCharacteristics::setStrength(int s)
{
    strength = s;
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

int FighterCharacteristics::getStrength() const
{
    return strength;
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

bool FighterCharacteristics::canAtkPunch() const
{
    return fightAtkPunch.canDoEffect();
}

bool FighterCharacteristics::canBlock() const
{
    return fightBlock.canDoEffect();
}