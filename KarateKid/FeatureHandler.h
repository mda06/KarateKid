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

class FeatureHandler
{
private:
    Texture texture;
    Animation idleAnim, walkAnim, runAnim, jumpAnim, atkFAnim, atkPAnim, hitAnim, deadAnim;
    AnimatedSprite animatedSprite;
    AnimationType type;
    Vector2f size;
    FighterCharacteristics fighterChar;
    bool isAnimDeadFinished;
    bool enemy;
    
public:
    FeatureHandler(Vector2f pos, Vector2f size, int maxHealth, int maxStrength, float blockWaitTime, float atkPunchCooldown, float atkFootCooldown, bool enemy);
    void update(Time time);
    void setType(AnimationType type, Entity* launcher = NULL, Entity* receiver = NULL);
    void move(Vector2f move);
    void init();
    bool isDeadAnimFinished() const;
    void setDeadAnimFinished(bool b);
    AnimationType getType() const;
    AnimatedSprite &getSprite();
    Vector2f getPosition() const;
    bool isAnimationFinished() const;
    FighterCharacteristics& getFighterCharacteristics();
    Vector2f getSize();
    
};

#endif /* defined(__KarateKid__AnimationHandler__) */
