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

Entity::Entity(CollisionHandler *col, Vector2f pos, bool withBack, int maxHealth, int maxStrength, float blockWaitTime, float atkPunchCooldown, float atkFootCooldown) : accel(2, 1), deccel(1.7f, 2.f), maxVel(.8f, .9f), colHandler(col), initialPos(pos), gbHealth(resourcePath() + "barre_hp_vide.png", resourcePath() + "barre_hp_couleur.png", Vector2f(10, 70), 126, withBack), animationHandler(AnimationHandler(maxHealth, maxStrength, blockWaitTime, atkPunchCooldown, atkFootCooldown))
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
    animationHandler.getSprite().setPosition(initialPos);
    animationHandler.init();
}

void Entity::update(Time time)
{
    animationHandler.update(time);
    updateGUIBar();
    if(!getFighterCharacteristics().isDead())
        handleMovement(time.asSeconds());
}

void Entity::updateGUIBar()
{
    FighterCharacteristics fc = getFighterCharacteristics();
    gbHealth.setPerc((float)fc.getHealth() / fc.getMaxHealth());
    
    std::stringstream stream;
    stream << fc.getHealth() << " / " << fc.getMaxHealth();
    txtHp.setString(stream.str());
    txtHp.setPosition(gbHealth.getPos().x + (gbHealth.getWidth() / 2), gbHealth.getPos().y + 5);
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
        
        if (!colEntity && canClimb(dt))
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
    rt.draw(animationHandler.getSprite());
}

void Entity::setDirection(Direction dir)
{
    if(getFighterCharacteristics().isDead()) return;
    
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
    if(getFighterCharacteristics().isDead()) return;
    
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

void Entity::drawHpBar(RenderTarget &rt)
{
    gbHealth.draw(rt);
    rt.draw(txtHp);
}