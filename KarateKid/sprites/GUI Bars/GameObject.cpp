//
//  MapObject.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 11/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "GameObject.h"
#include "ResourcePath.hpp"

GameObject::GameObject(std::string path, Vector2f pos)
{
    if(!texture.loadFromFile(path))
        std::cout << "Can't load mapObject " << path << std::endl;
    
    sprite.setTexture(texture);
    sprite.setPosition(pos.x, pos.y);
    isUse = false;
    a = 0;
    yBase = pos.y;
    
    std::cout << "Added gameObject at " << pos.x << "/" << pos.y << std::endl;
}

GameObject::~GameObject()
{}

void GameObject::update(float dt)
{
    a += 1 * dt;
    sprite.setPosition(sprite.getPosition().x, yBase + cos(a) * 25);
    std::cout << sprite.getPosition().y << std::endl;
    //e.posX = w/2 + Math.cos(e.cosX += 0.007) * w / 2;
}

void GameObject::effect(Entity *target)
{
    isUse = true;
}

void GameObject::draw(sf::RenderTarget &rt)
{
    rt.draw(sprite);
}

FloatRect GameObject::getBounds() const
{
    return sprite.getGlobalBounds();
}

bool GameObject::isUsed() const
{
    return isUse;
}

GameObjectPotion::GameObjectPotion(Vector2f pos) : GameObject(resourcePath() + "potionHealth.png", pos)
{
}

void GameObjectPotion::effect(Entity *target)
{
    GameObject::effect(nullptr);
    //target->getFighterCharacteristics().addMaxStrength(5);
    target->getFighterCharacteristics().addHealth(50);
}