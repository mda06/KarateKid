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
#include "Entity.h"
using namespace sf;

class GameObject
{
private:
    Sprite sprite;
    Texture texture;
    bool isUse;
    
public:
    GameObject(std::string path, Vector2f pos);
    virtual ~GameObject();
    virtual void effect(Entity* target);
    void update(float dt);
    void draw(RenderTarget &rt);
    bool isUsed() const;
    FloatRect getBounds() const;
};

class GameObjectPotion : public GameObject
{
public:
    GameObjectPotion(Vector2f pos);
    virtual void effect(Entity* target);
};


#endif /* defined(__KarateKid__MapObject__) */