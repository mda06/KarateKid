//
//  MapObject.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 11/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__MapObject__
#define __KarateKid__MapObject__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"
using namespace sf;

class ScreenManager;

class GameObject
{
private:
    Sprite sprite;
    Texture texture;
    bool isUse;
    SoundBuffer buf;
    Sound sound;
    Vector2f pos;
    
protected:
    String text;
    
public:
    GameObject(std::string path, Vector2f pos);
    virtual ~GameObject();
    virtual void effect(Entity* target);
    void update(float dt);
    void draw(RenderTarget &rt);
    bool isUsed() const;
    FloatRect getBounds() const;
    Vector2f getPos();
    String getString();
};

class GameObjectPotion : public GameObject
{
public:
    GameObjectPotion(Vector2f pos);
    virtual void effect(Entity* target);
};

class GameObjectStrength : public GameObject
{
public:
    GameObjectStrength(Vector2f pos);
    virtual void effect(Entity* target);
};

class GameObjectEnergy : public GameObject
{
public:
    GameObjectEnergy(Vector2f pos);
    virtual void effect(Entity* target);
};

class GameObjectKey : public GameObject
{
private:
    ScreenManager* sm;
public:
    GameObjectKey(ScreenManager* sm, Vector2f pos);
    virtual void effect(Entity* target);
};

#endif /* defined(__KarateKid__MapObject__) */
