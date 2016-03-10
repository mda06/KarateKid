//
//  Entity.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 29/02/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__Entity__
#define __KarateKid__Entity__

#include "AnimationHandler.h"
#include <SFML/Graphics.hpp>
#include <tmx/MapLoader.h>
#include "CollisionHandler.h"
#include "GUIBar.h"
#include "SoundManager.h"
using namespace sf;

enum Direction
{
    STOP,
    LEFT,
    RIGHT
};

class Entity
{
protected:
    Vector2f vel, maxVel, accel, deccel;
    Direction direction;
    AnimationHandler animationHandler;
    CollisionHandler *colHandler;
    void handleMovement(float dt);
    Vector2f initialPos;
    GUIBar gbHealth;
    virtual void updateGUIBar();
    bool canClimb(float dt);
    Font font;
    Text txtHp;
    bool enableFootAtk;
    SoundManager sound;
    
public:
    Entity(CollisionHandler *col, Vector2f pos, bool withBack, int maxHealth, int maxStrength, float blockWaitTime, float atkPunchCooldown, float atkFootCooldown, bool enableFootAtk = false);
    void init();
    virtual void update(Time time);
    void render(RenderTarget &rt);
    Vector2f getPosition() const;
    void setMaxVel(Vector2f v);
    void setAccel(Vector2f v);
    void setDirection(Direction dir);
    void setOrientation(Direction dir);
    void setColor(Color color);             
    GUIBar &getHealthBar();
    void jump();
    void attackFoot();
    void attackPunch();
    void block();
    void setDeadAnimFinished(bool b);
    bool isDeadAnimFinished() const;
    FloatRect getGlobalBounds();
    FighterCharacteristics &getFighterCharacteristics();
    void drawHpBar(RenderTarget &rt);
};

#endif /* defined(__KarateKid__Entity__) */
