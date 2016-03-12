//
//  Entity.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 29/02/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "Entity.h"
#include "ResourcePath.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

Entity::Entity(CollisionHandler *col, Vector2f pos, bool withBack, int maxHealth, int maxStrength, float blockWaitTime, float atkPunchCooldown, float atkFootCooldown, bool fatk) : accel(2, 1), deccel(1.7f, 2.f), maxVel(.8f, .9f), colHandler(col), initialPos(pos), gbHealth(resourcePath() + "barre_hp_vide.png", resourcePath() + "barre_hp_couleur.png", Vector2f(10, 70), 126, withBack), featureHandler(FeatureHandler(maxHealth, maxStrength, blockWaitTime, atkPunchCooldown, atkFootCooldown)), enableFootAtk(fatk)
{
    if(!font.loadFromFile(resourcePath() + "master_of_break.ttf"))
        std::cout << "Can't load font !" << std::endl;
    txtHp.setFont(font);
    txtHp.setCharacterSize(7);
}

void Entity::init()
{
    direction = STOP;
    vel = Vector2f();
    featureHandler.getSprite().setPosition(initialPos);
    featureHandler.init();
}

void Entity::update(Time time)
{
    featureHandler.update(time);
    updateGUIBar();
    if(!getFighterCharacteristics().isDead())
        handleMovement(time.asSeconds());
    colHandler->handleGameObjects(this);
}

void Entity::updateGUIBar()
{
    FighterCharacteristics fc = getFighterCharacteristics();
    gbHealth.setPerc((float)fc.getHealth() / fc.getMaxHealth());
    
    std::stringstream stream;
    stream << fc.getHealth() << " / " << fc.getMaxHealth();
    txtHp.setString(stream.str());
    txtHp.setPosition(gbHealth.getPos().x + (gbHealth.getWidth() / 4), gbHealth.getPos().y - 2);
}

void Entity::handleMovement(float dt)
{
    if(direction == LEFT) vel.x -= accel.x * dt;
    else if(direction == RIGHT) vel.x += accel.x * dt;
    else
    {
        if(vel.x > 0)
        {
            vel.x -= deccel.x * dt;
            if(vel.x <= 0) vel.x = 0;
        }
        else
        {
            vel.x += deccel.x * dt;
            if(vel.x >= 0) vel.x = 0;
        }
    }
    
    bool wasVelXNull = vel.x == 0;
    
    if(vel.x > maxVel.x) vel.x = maxVel.x;
    if(vel.x < -maxVel.x) vel.x = -maxVel.x;
    
    vel.y += deccel.y * dt;
    if(vel.y > maxVel.y)
        vel.y = maxVel.y;
    
    Vector2f movement;
    FloatRect bounds = getGlobalBounds();
    bounds.left += vel.x;
    bool colEntity = colHandler->collisionWithEntity(this, bounds);
    if(colHandler->canMove(bounds) && !colEntity)
    {
        movement.x += vel.x;
    }
    else
    {
        vel.x = 0;
        
        if (!colEntity && canClimb(dt))
            vel.y -= accel.y * dt * 5;
    }
    
    bounds = getGlobalBounds();
    bounds.top += vel.y;
    if(colHandler->canMove(bounds) && !colHandler->collisionWithEntity(this, bounds))
        movement.y += vel.y;
    else
        vel.y = 0;
    
    featureHandler.move(movement);
    
    if(vel.x > 0)
    {
        if(vel.x == maxVel.x){
            if(featureHandler.getType() != RUN)
                featureHandler.setType(RUN);
        }
        else
            featureHandler.setType(WALK);
    }
    else if(vel.x < 0)
    {
        if(vel.x == -maxVel.x){
            if(featureHandler.getType() != RUN)
                featureHandler.setType(RUN);
        }
        else
            featureHandler.setType(WALK);
    }
    else if(wasVelXNull && featureHandler.getType() == WALK)
        featureHandler.setType(IDLE);
}

bool Entity::canClimb(float dt)
{
    FloatRect bounds = getGlobalBounds();
    bool colEntity = colHandler->collisionWithEntity(this, bounds);
    
    bounds.left += 1;               // change bounds -> only look for collision with ground
    bounds.width -= 2;
    bounds.height += 25;            // he can climb 25 pixels
    
    if(!colHandler->canMove(bounds))    // can't climb if he is not on the ground
    {
        bounds = getGlobalBounds();     // reset bounds
        bounds.top -= 25;               // change bounds -> what will happen if he climbs 25 px?
        bounds.left -= 1;               // make 1 px bigger to check collision
        bounds.width += 2;
        if (colHandler->canMove(bounds))// no collision? -> can climb
            return true;
        else
            return false;
    }
    else
        return false;
}

void Entity::render(RenderTarget &rt)
{
    rt.draw(featureHandler.getSprite());
}

void Entity::setDirection(Direction dir)
{
    if(getFighterCharacteristics().isDead()) return;
    
    direction = dir;
    AnimationType curType = featureHandler.getType();
    switch(dir)
    {
        case STOP : if(curType != IDLE) featureHandler.setType(IDLE); break;
        case LEFT: if(curType != WALK && curType != RUN) featureHandler.setType(WALK);
            if(featureHandler.getSprite().getScale().x > 0) featureHandler.getSprite().scale(-1, 1);
            break;
        case RIGHT: if(curType != WALK && curType != RUN) featureHandler.setType(WALK);
            if(featureHandler.getSprite().getScale().x < 0) featureHandler.getSprite().scale(-1, 1);
            break;
    }
}

void Entity::setOrientation(Direction dir)
{
    if(getFighterCharacteristics().isDead()) return;
    
    switch(dir)
    {
        case LEFT: if(featureHandler.getSprite().getScale().x > 0) featureHandler.getSprite().scale(-1, 1);
            break;
        case RIGHT: if(featureHandler.getSprite().getScale().x < 0) featureHandler.getSprite().scale(-1, 1);
            break;
            
        default: break;
    }

}

void Entity::jump()
{
    FloatRect bounds = getGlobalBounds();
    bounds.top += 1;
    if(!colHandler->canMove(bounds) || colHandler->collisionWithEntity(this, bounds))
    {
        vel.y = -maxVel.y;
        //animationHandler.setType(JUMP);
    }
}

void Entity::setColor(Color color)
{
    featureHandler.getSprite().setColor(color);
}

void Entity::attackFoot()
{
    if(!enableFootAtk) return;
    
    FloatRect bd = getGlobalBounds();
    if(featureHandler.getSprite().getScale().x < 0)
        bd.left -= getFighterCharacteristics().getRangeHit();
    else
        bd.left += getFighterCharacteristics().getRangeHit();
    featureHandler.setType(ATTACK_FOOT, this, colHandler->getCollsionWithEntity(this, bd));
}

void Entity::attackPunch()
{
    if(!featureHandler.getFighterCharacteristics().canAtkPunch()) return;
    
    FloatRect bd = getGlobalBounds();
    if(featureHandler.getSprite().getScale().x < 0)
        bd.left -= getFighterCharacteristics().getRangeHit();
    else
        bd.left += getFighterCharacteristics().getRangeHit();
    featureHandler.setType(ATTACK_PUNCH, this, colHandler->getCollsionWithEntity(this, bd));
    
    sound.playPunch();
}

void Entity::block()
{
    featureHandler.setType(BLOCK, NULL, NULL);
}

FighterCharacteristics& Entity::getFighterCharacteristics()
{
    return featureHandler.getFighterCharacteristics();
}

void Entity::setMaxVel(Vector2f v)
{
    maxVel = v;
}

void Entity::setAccel(Vector2f v)
{
    accel = v;
}

GUIBar &Entity::getHealthBar()
{
    return gbHealth;
}

Vector2f Entity::getPosition() const
{
    return featureHandler.getPosition();
}

void Entity::setDeadAnimFinished(bool b)
{
    featureHandler.setDeadAnimFinished(b);
}

bool Entity::isDeadAnimFinished() const
{
    return featureHandler.isDeadAnimFinished();
}

FloatRect Entity::getGlobalBounds()
{
    return (featureHandler.getSprite().getGlobalBounds());
}

void Entity::drawHpBar(RenderTarget &rt)
{
    gbHealth.draw(rt);
    rt.draw(txtHp);
}