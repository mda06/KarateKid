//
//  FightState.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 5/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__FightState__
#define __KarateKid__FightState__

class Entity;

class AbstractFightState
{
protected:
    float curCooldown, cooldown;
    float curActiveCooldown, activeCooldown;    
public:
    AbstractFightState(float active, float cooldown);
    void update(float dt);
    void setCooldown(float c);
    void setActiveCooldown(float c);
    bool canDoEffect() const;
    bool finishEffect() const;
    virtual void effect(Entity *launcher, Entity *receiver) = 0;
};

class FightStateNormal : public AbstractFightState
{
public:
    FightStateNormal();
    void effect(Entity *launcher, Entity *receiver);
};


class FightStateAttack : public AbstractFightState
{
public:
    FightStateAttack(float act);
    void effect(Entity *launcher, Entity *receiver);
};


class FightStateBlock : public AbstractFightState
{
public:
    FightStateBlock(float act);
    void effect(Entity *launcher, Entity *receiver);
};



#endif /* defined(__KarateKid__FightState__) */
