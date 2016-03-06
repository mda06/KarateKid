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
#include "FighterCharacteristics.h"
#include <SFML/Graphics.hpp>
using namespace sf;

enum AnimationType
{
    IDLE, WALK, RUN, JUMP, ATTACK_FOOT, ATTACK_PUNCH, BLOCK, DEAD
};

class AnimationHandler
{
private:
    Texture texture;
    Animation idleAnim, walkAnim, runAnim, jumpAnim, atkFAnim, atkPAnim, hitAnim, deadAnim;
    AnimatedSprite animatedSprite;
    AnimationType type;
    Vector2f size;
    FighterCharacteristics fighterChar;
    float timeAtkFoot, timeAtkPunch, timeBlock;
    
public:
    AnimationHandler();
    void update(Time time);
    void setType(AnimationType type, Entity* launcher = NULL, Entity* receiver = NULL);
    void move(Vector2f move);
    AnimationType getType() const;
    AnimatedSprite &getSprite();
    Vector2f getPosition() const;
    bool isAnimationFinished() const;
    FighterCharacteristics& getFighterCharacteristics();
};

#endif /* defined(__KarateKid__AnimationHandler__) */
