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

Entity::Entity(CollisionHandler *col, Vector2f pos) : accel(2, 1), deccel(1.4f, 2.f), maxVel(.8f, .9f), colHandler(col), initialPos(pos), gbHealth(resourcePath() + "barre_hp_vide.png", resourcePath() + "barre_hp_couleur.png", Vector2f(10, 70), 126, true), gbEnergy(resourcePath() + "barre_energie_vide.png", resourcePath() + "barre_energie_couleur.png", Vector2f(10, 100), 126, true), gbStrength(resourcePath() + "barre_force_vide.png", resourcePath() + "barre_force_couleur.png", Vector2f(10, 130), 126, true)
{
}

void Entity::init()
{
    direction = STOP;
    vel = Vector2f();
    animationHandler.getSprite().setPosition(initialPos);
    animationHandler.init();
}

void Entity::update(Time time)
{
    animationHandler.update(time);
    updateGUIBar();
    handleMovement(time.asSeconds());
}

void Entity::updateGUIBar()
{
    FighterCharacteristics fc = getFighterCharacteristics();
    
    gbHealth.setPerc((float)fc.getHealth() / fc.getMaxHealth());
    gbEnergy.setPerc((float)fc.getBlockState().getCurActiveCooldown() / fc.getBlockState().getActiveCooldown());
    gbStrength.setPerc((float)fc.getCurrStrength() / (float)fc.getMaxStrength());
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
        
        // change bounds -> only look for collision with ground
        bounds.left += 5;
        bounds.width -= 10;
        bounds.top += 25; // he can climb 25 pixels
        
        //To climb but not on enemies and not if he is not on the ground
        if(!colEntity && !colHandler->canMove(bounds))
            vel.y -= accel.y * dt * 5;
    }
    
    bounds = getGlobalBounds();
    bounds.top += vel.y;
    if(colHandler->canMove(bounds) && !colHandler->collisionWithEntity(this, bounds))
        movement.y += vel.y;
    else
        vel.y = 0;
    
    animationHandler.move(movement);
}

void Entity::render(RenderTarget &rt)
{
    rt.draw(animationHandler.getSprite());
}

void Entity::setDirection(Direction dir)
{
    direction = dir;
    AnimationType curType = animationHandler.getType();
    switch(dir)
    {
        case STOP : if(curType != IDLE) animationHandler.setType(IDLE); break;
        case LEFT: if(curType != WALK) animationHandler.setType(WALK);
            if(animationHandler.getSprite().getScale().x > 0) animationHandler.getSprite().scale(-1, 1);
            break;
        case RIGHT: if(curType != WALK) animationHandler.setType(WALK);
            if(animationHandler.getSprite().getScale().x < 0) animationHandler.getSprite().scale(-1, 1);
            break;
    }
}

void Entity::setOrientation(Direction dir)
{
    switch(dir)
    {
        case LEFT: if(animationHandler.getSprite().getScale().x > 0) animationHandler.getSprite().scale(-1, 1);
            break;
        case RIGHT: if(animationHandler.getSprite().getScale().x < 0) animationHandler.getSprite().scale(-1, 1);
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
    animationHandler.getSprite().setColor(color);
}

void Entity::attackFoot()
{
    FloatRect bd = getGlobalBounds();
    bd.left += animationHandler.getSprite().getScale().x * getFighterCharacteristics().getRangeHit();
    animationHandler.setType(ATTACK_FOOT, this, colHandler->getCollsionWithEntity(this, bd));
}

void Entity::attackPunch()
{
    if(getFighterCharacteristics().canAtkPunch())
        getFighterCharacteristics().addStrength(getFighterCharacteristics().getStrengthDiff());
    
    FloatRect bd = getGlobalBounds();
    bd.left += animationHandler.getSprite().getScale().x * getFighterCharacteristics().getRangeHit();
    animationHandler.setType(ATTACK_PUNCH, this, colHandler->getCollsionWithEntity(this, bd));    
}

void Entity::block()
{
    animationHandler.setType(BLOCK, NULL, NULL);
}

FighterCharacteristics& Entity::getFighterCharacteristics()
{
    return animationHandler.getFighterCharacteristics();
}

void Entity::setMaxVel(Vector2f v)
{
    maxVel = v;
}

void Entity::setAccel(Vector2f v)
{
    accel = v;
}

void Entity::setGUIBarOnBack(bool withBack)
{
    gbHealth.setWithBack(withBack);
    gbEnergy.setWithBack(withBack);
    gbStrength.setWithBack(withBack);
}

GUIBar &Entity::getHealthBar()
{
    return gbHealth;
}

Vector2f Entity::getPosition() const
{
    return animationHandler.getPosition();
}

bool Entity::isDeadAnimFinished() const
{
    return animationHandler.isDeadAnimFinished();
}

FloatRect Entity::getGlobalBounds()
{
    return (animationHandler.getSprite().getGlobalBounds());
}

void Entity::drawHpBar(RenderTarget &rt, bool aboveEntity)
{
    gbHealth.draw(rt);
}

void Entity::drawEnergyBar(RenderTarget &rt)
{
    gbEnergy.draw(rt);
}

void Entity::drawStrengthBar(RenderTarget &rt)
{
    gbStrength.draw(rt);
}