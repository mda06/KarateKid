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
bool AbstractFightState::canDoEffect() const
{
    return curCooldown <= 0;
}

bool AbstractFightState::finishEffect() const
{
    return curActiveCooldown <= 0;
}

FightStateNormal::FightStateNormal() : AbstractFightState(0, 0)
{}

void FightStateNormal::effect(Entity *launcher, Entity *receiver)
{
    std::cout << "Effect of normal" << std::endl;
}

FightStateBlock::FightStateBlock(float act) : AbstractFightState(act, .7f)
{}

void FightStateBlock::effect(Entity *launcher, Entity *receiver)
{
    curCooldown = cooldown;
    curActiveCooldown = activeCooldown;
    std::cout << "Effect of block" << std::endl;
}

FightStateAttack::FightStateAttack(float act) : AbstractFightState(act, .6f)
{}

void FightStateAttack::effect(Entity *launcher, Entity *receiver)
{
    curCooldown = cooldown;
    curActiveCooldown = activeCooldown;
    std::cout << "Effect of Atk" << std::endl;
    if(launcher != NULL && receiver != NULL)
    {
        std::cout << "\t HIT !" << std::endl;
    }
}