//
//  AnimationHandler.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 3/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__AnimationHandler__
#define __KarateKid__AnimationHandler__

#include "AnimatedSprite.h"
#include <SFML/Graphics.hpp>
using namespace sf;

enum AnimationType
{
    IDLE, WALK, RUN, JUMP, ATTACK_FOOT, ATTACK_PUNCH, HIT, DEAD
};

class AnimationHandler
{
private:
    Texture texture;
    Animation idleAnim, walkAnim, runAnim, jumpAnim, atkFAnim, atkPAnim, hitAnim, deadAnim;
    AnimatedSprite animatedSprite;
    AnimationType type;
    Vector2f size;
    
public:
    AnimationHandler();
    void update(Time time);
    void setType(AnimationType type);
    void move(Vector2f move);
    AnimationType getType() const;
    AnimatedSprite getSprite();
    Vector2f getPosition() const;
    //pos
    //move
    //draw
};

#endif /* defined(__KarateKid__AnimationHandler__) */
