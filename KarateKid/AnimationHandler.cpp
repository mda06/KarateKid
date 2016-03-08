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

AnimationHandler::AnimationHandler(int maxHealth, int maxStrength, float blockWaitTime, float atkPunchCooldown, float atkFootCooldown): size(48, 48), type(IDLE), animatedSprite(seconds(1)), isAnimDeadFinished(false), fighterChar(maxHealth, maxStrength, blockWaitTime, atkPunchCooldown, atkFootCooldown)
{
    if(!texture.loadFromFile(resourcePath() + "blond.png"))
        std::cout << "Failed to load texture in AnimationHandler" << std::endl;
    
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
    atkFAnim.addFrame(IntRect(11, 766, 93, 162));
    atkFAnim.addFrame(IntRect(134, 766, 215, 162));
    atkFAnim.addFrame(IntRect(360, 766, 212, 162));
     
    atkPAnim.setSpriteSheet(texture);
    atkPAnim.addFrame(IntRect(11, 936, 93, 214));
    atkPAnim.addFrame(IntRect(128, 936, 115, 214));
    atkPAnim.addFrame(IntRect(273, 936, 115, 214));
    
    hitAnim.setSpriteSheet(texture);
    hitAnim.addFrame(IntRect(11, 1161, 93, 161));
    hitAnim.addFrame(IntRect(146, 1161, 96, 161));

    deadAnim.setSpriteSheet(texture);
    deadAnim.addFrame(IntRect(14, 1358, 96, 161));
    deadAnim.addFrame(IntRect(127, 1358, 96, 161));
    deadAnim.addFrame(IntRect(242, 1358, 96, 161));
    deadAnim.addFrame(IntRect(351, 1358, 102, 161));
    deadAnim.addFrame(IntRect(467, 1358, 100, 161));
 
    animatedSprite.play(idleAnim);
    
    animatedSprite.setScale(size.x / 100, size.y / 160);
    animatedSprite.setPosition(20, 50);
    animatedSprite.setOrigin(animatedSprite.getGlobalBounds().width, animatedSprite.getGlobalBounds().height);
}

void AnimationHandler::update(Time time)
{
    fighterChar.update(time.asSeconds());
    animatedSprite.update(time);
    if(isAnimationFinished())
    {
        switch(type)
        {
            case ATTACK_FOOT: setType(IDLE); break;
            case ATTACK_PUNCH: setType(IDLE); break;
            case DEAD: isAnimDeadFinished = true; break;
            default: break;
        }
    }
    if(!fighterChar.getBlockState().canDoEffect() && type == BLOCK)
        setType(IDLE);
    
    if(fighterChar.isDead() && type != DEAD)
        setType(DEAD);
}

void AnimationHandler::move(Vector2f move)
{
    animatedSprite.move(move);
}

void AnimationHandler::setType(AnimationType type, Entity* launcher, Entity* receiver)
{
    switch(type)
    {
        case ATTACK_FOOT: if(fighterChar.canAtkFoot()) {
            fighterChar.setFightState(ATTACK_FOOT_STATE);
            fighterChar.effect(launcher, receiver);
            animatedSprite.play(atkFAnim);
            animatedSprite.setFrameTime(seconds(.1f));
            animatedSprite.setLooped(false);
        } break;
        case ATTACK_PUNCH: if(fighterChar.canAtkPunch()) {
            fighterChar.setFightState(ATTACK_PUNCH_STATE);
            fighterChar.effect(launcher, receiver);
            animatedSprite.play(atkPAnim);
            animatedSprite.setFrameTime(seconds(.1f));
            animatedSprite.setLooped(false);
        } break;
        case BLOCK: if(fighterChar.canBlock()) {
            fighterChar.setFightState(BLOCK_STATE);
            fighterChar.effect(launcher, receiver);
            animatedSprite.play(hitAnim);
            animatedSprite.setFrame(1);
            animatedSprite.pause();
        }break;
            
        default: fighterChar.setFightState(NORMAL_STATE); break;
    }
    
    this->type = type;
    switch(this->type)
    {
        case IDLE:  animatedSprite.play(idleAnim);
                    animatedSprite.setFrameTime(seconds(1)); break;
        case WALK:  animatedSprite.play(walkAnim);
                    animatedSprite.setFrameTime(seconds(.08f)); break;
        case RUN:   animatedSprite.play(runAnim);
                    animatedSprite.setFrameTime(seconds(.4f)); break;
        case JUMP:  animatedSprite.play(jumpAnim);
                    animatedSprite.setFrameTime(seconds(.14f));
                    animatedSprite.setLooped(false); break;
        case DEAD:  animatedSprite.play(deadAnim);
                    animatedSprite.setFrameTime(seconds(.3f));
                    animatedSprite.setLooped(false); break;
        default: break;
    }
}

bool AnimationHandler::isDeadAnimFinished() const
{
    return isAnimDeadFinished;
}

bool AnimationHandler::isAnimationFinished() const
{
    return !animatedSprite.isPlaying();
}

void AnimationHandler::init()
{
    isAnimDeadFinished = false;
    setType(IDLE);
    animatedSprite.play();
    fighterChar.init();
}

Vector2f AnimationHandler::getPosition() const
{
    return animatedSprite.getPosition();
}

AnimationType AnimationHandler::getType() const
{
    return type;
}

FighterCharacteristics& AnimationHandler::getFighterCharacteristics()
{
    return fighterChar;
}

AnimatedSprite &AnimationHandler::getSprite()
{
    return animatedSprite;
}