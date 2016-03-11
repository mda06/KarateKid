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
    float initStrength, currStrength, maxStrength, strengthDiff, recupStrength;
    
public:
    FighterCharacteristics(int maxHealth, int maxStrength, float blockWaitTime, float atkPunchCooldown, float atkFootCooldown);
    void init();
    void update(float dt);
    void setFightState(FightState fs);
    void effect(Entity* launcher, Entity* receiver);
    void hit(int dmg);
    void setHealthAndMaxHealth(int h);
    void setStrength(int s);
    void addStrength(float s);
    void addMaxStrength(float s);
    void addHealth(int s);
    int getHealth() const;
    int getMaxHealth() const;
    int getRangeHit() const;
    int getCurrStrength() const;
    int getMaxStrength() const;
    int getStrengthDiff() const;
    int getDamages() const;
    bool isDead() const;
    bool canAtkFoot() const;
    bool canAtkPunch() const;
    bool canBlock() const;
    FightState getFightState() const;
    FightStateAttack &getAtkFootState();
    FightStateBlock &getBlockState();
    FightStateAttack &getAtkPunchState();
};

#endif /* defined(__KarateKid__FighterCharacteristics__) */
