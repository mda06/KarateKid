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
    idleAnim.addFrame(IntRect(124, 0, 93, 161));
    idleAnim.addFrame(IntRect(237, 0, 94, 161));
    idleAnim.addFrame(IntRect(350, 0, 94, 161));
    
    walkAnim.setSpriteSheet(texture);
    walkAnim.addFrame(IntRect(11, 189, 93, 160));
    walkAnim.addFrame(IntRect(123, 189, 93, 160));
    walkAnim.addFrame(IntRect(234, 189, 95, 160));
    walkAnim.addFrame(IntRect(346, 189, 95, 160));
    walkAnim.addFrame(IntRect(459, 189, 94, 160));
 
    jumpAnim.setSpriteSheet(texture);
    jumpAnim.addFrame(IntRect(11, 547, 93, 184));
    jumpAnim.addFrame(IntRect(122, 547, 104, 184));
    jumpAnim.addFrame(IntRect(259, 547, 93, 184));
    jumpAnim.addFrame(IntRect(380, 547, 106, 184));
    
    runAnim.setSpriteSheet(texture);
    atkFAnim.setSpriteSheet(texture);
    atkPAnim.setSpriteSheet(texture);
    hitAnim.setSpriteSheet(texture);
    deadAnim.setSpriteSheet(texture);
 
    animatedSprite.play(idleAnim);
    animatedSprite.setScale(size.x / 100, size.y / 160);
    animatedSprite.setPosition(20, 50);
    animatedSprite.setOrigin(animatedSprite.getGlobalBounds().width, animatedSprite.getGlobalBounds().height);
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
        case JUMP: animatedSprite.play(jumpAnim); animatedSprite.setFrameTime(seconds(.14f)); animatedSprite.setLooped(false); break;
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

AnimatedSprite &AnimationHandler::getSprite()
{
    return animatedSprite;
}