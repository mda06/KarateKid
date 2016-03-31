//
//  Entity.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 29/02/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__Entity__
#define __KarateKid__Entity__

#include "FeatureHandler.h"
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
    FeatureHandler featureHandler;
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
    void syncAnimationWithVel(bool wasVelXNull);
    bool updateVelX(float dt);
    void updateVelY(float dt);
    float checkColX(float dt);
    float checkColY(float dt);
    
public:
    Entity(CollisionHandler *col, Vector2f pos, Vector2f size, bool withBack, int maxHealth, int maxStrength, float blockWaitTime, float atkPunchCooldown, float atkFootCooldown, bool enemy, bool enableFootAtk = false);
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
