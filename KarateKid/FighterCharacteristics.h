//
//  FighterCharacteristics.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 5/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__FighterCharacteristics__
#define __KarateKid__FighterCharacteristics__

#include "FightState.h"

enum FightState
{
    NORMAL_STATE,
    BLOCK_STATE,
    ATTACK_FOOT_STATE,
    ATTACK_PUNCH_STATE
};

class FighterCharacteristics
{
private:
    FightStateAttack fightAtkPunch, fightAtkFoot;
    FightStateBlock fightBlock;
    FightStateNormal fightNormal;
    FightState state;
    int maxHealth, health;
    int rangeHit;
    float strength;
    
public:
    FighterCharacteristics();
    void update(float dt);
    void setFightState(FightState fs);
    void effect(Entity* launcher, Entity* receiver);
    void hit(int dmg);
    void setHealthAndMaxHealth(int h);
    void setStrength(int s);
    int getHealth() const;
    int getMaxHealth() const;
    int getRangeHit() const;
    int getStrength() const;
    bool isDead() const;
    bool canAtkFoot() const;
    bool canAtkPunch() const;
    bool canBlock() const;
    FightState getFightState() const;
};

#endif /* defined(__KarateKid__FighterCharacteristics__) */
