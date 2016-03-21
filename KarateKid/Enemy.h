//
//  Enemy.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 8/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__Enemy__
#define __KarateKid__Enemy__

#include "Entity.h"

class Enemy : public Entity
{
private:
    int targetRange;
    bool isEntityUpOrDown(Entity *target);
    void moveLeft(float ex, float px, Entity *target);
    void moveRight(float ex, float px, Entity *target);
    
public:
    Enemy(CollisionHandler *col, Vector2f pos, int maxHealth, int maxStrength, float blockWaitTime, float atkPunchCooldown, float atkFootCooldown, Vector2f size);
    virtual void update(Time time);
    void updateTarget(Entity* target);
};

#endif /* defined(__KarateKid__Enemy__) */
