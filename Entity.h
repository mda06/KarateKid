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
using namespace sf;

enum Direction
{
    STOP,
    LEFT,
    RIGHT
};

class Entity
{
private:
    Vector2f vel, maxVel, accel, deccel;
    Direction direction;
    AnimationHandler animationHandler;
    CollisionHandler *colHandler;
    void handleMovement(float dt);
    Vector2f initialPos;
    GUIBar gbHealth, gbEnergy, gbStrength;
    
public:
    Entity(CollisionHandler *col, Vector2f pos = Vector2f());
    void init();
    void update(Time time);
    void updateGUIBar();
    void render(RenderTarget &rt);
    Vector2f getPosition() const;
    void setMaxVel(Vector2f v);
    void setAccel(Vector2f v);
    void setDirection(Direction dir);
    void setOrientation(Direction dir);
    void setColor(Color color);
    void setGUIBarOnBack(bool withBack);
    GUIBar &getHealthBar();
    void jump();
    void attackFoot();
    void attackPunch();
    void block();
    void dead();
    bool isDeadAnimFinished() const;
    FloatRect getGlobalBounds();
    FighterCharacteristics &getFighterCharacteristics();
    void drawHpBar(RenderTarget &rt, bool aboveEntity = false);
    void drawEnergyBar(RenderTarget &rt);
    void drawStrengthBar(RenderTarget &rt);
    
};

#endif /* defined(__KarateKid__Entity__) */
