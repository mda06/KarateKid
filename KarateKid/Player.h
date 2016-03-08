//
//  Player.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 8/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__Player__
#define __KarateKid__Player__

#include "Entity.h"

class Player : public Entity
{
private:
    GUIBar gbEnergy, gbStrength;
    
public:
    Player(CollisionHandler *col, Vector2f pos);
    virtual void updateGUIBar();
    void drawEnergyBar(RenderTarget &rt);
    void drawStrengthBar(RenderTarget &rt);

};

#endif /* defined(__KarateKid__Player__) */
