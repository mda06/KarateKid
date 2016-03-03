//
//  AnimationHandler.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 3/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "AnimationHandler.h"
#include "ResourcePath.hpp"
#include <iostream>

AnimationHandler::AnimationHandler(): size(48, 48), type(IDLE), animatedSprite(seconds(.2f))
{
    //If fail ...
    texture.loadFromFile(resourcePath() + "blond.png");
    texture.setSmooth(true);
   
    idleAnim.setSpriteSheet(texture);
    idleAnim.addFrame(IntRect(11, 0, 93, 161));
    idleAnim.addFrame(IntRect(124, 4, 93, 157));
    idleAnim.addFrame(IntRect(237, 0, 94, 161));
    idleAnim.addFrame(IntRect(350, 4, 94, 157));
    
    walkAnim.setSpriteSheet(texture);
    walkAnim.addFrame(IntRect(11, 189, 93, 160));
    walkAnim.addFrame(IntRect(123, 193, 93, 156));
    walkAnim.addFrame(IntRect(234, 190, 95, 159));
    walkAnim.addFrame(IntRect(346, 189, 95, 160));
    walkAnim.addFrame(IntRect(459, 189, 94, 160));
  
    runAnim.setSpriteSheet(texture);
 
    jumpAnim.setSpriteSheet(texture);
    jumpAnim.addFrame(IntRect(11, 571, 93, 160));
    jumpAnim.addFrame(IntRect(122, 584, 104, 148));
    jumpAnim.addFrame(IntRect(259, 547, 93, 167));
    jumpAnim.addFrame(IntRect(380, 582, 106, 149));
  
    atkFAnim.setSpriteSheet(texture);
    atkPAnim.setSpriteSheet(texture);
    hitAnim.setSpriteSheet(texture);
    deadAnim.setSpriteSheet(texture);
 
    animatedSprite.play(idleAnim);
    
    //sprite.setTexture(texture);
    //sprite.setScale(size.x / 111, size.y / 161);
    //sprite.setOrigin(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
    //SIZE of animated sprite !!!
    
}

void AnimationHandler::update(Time time)
{
    animatedSprite.update(time);
}

void AnimationHandler::move(Vector2f move)
{
    animatedSprite.move(move);
}

void AnimationHandler::setType(AnimationType type)
{
    this->type = type;
    switch(type)
    {
        case IDLE: animatedSprite.play(idleAnim); animatedSprite.setFrameTime(seconds(1)); break;
        case WALK: animatedSprite.play(walkAnim); animatedSprite.setFrameTime(seconds(.08f)); break;
        case RUN: animatedSprite.play(runAnim); animatedSprite.setFrameTime(seconds(.4f)); break;
        case JUMP: animatedSprite.play(jumpAnim); animatedSprite.setFrameTime(seconds(.14f)); break;
        case ATTACK_FOOT: animatedSprite.play(atkFAnim); animatedSprite.setFrameTime(seconds(.4f)); break;
        case ATTACK_PUNCH: animatedSprite.play(atkPAnim); animatedSprite.setFrameTime(seconds(.4f)); break;
        case HIT: animatedSprite.play(hitAnim); animatedSprite.setFrameTime(seconds(.4f)); break;
        case DEAD: animatedSprite.play(deadAnim); animatedSprite.setFrameTime(seconds(.4f)); break;
    }
}

Vector2f AnimationHandler::getPosition() const
{
    return animatedSprite.getPosition();
}

AnimationType AnimationHandler::getType() const
{
    return type;
}

AnimatedSprite AnimationHandler::getSprite()
{
    return animatedSprite;
}