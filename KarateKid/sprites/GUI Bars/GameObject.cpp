//
//  MapObject.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 11/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//
//Hello 2

#include "GameObject.h"
#include "ResourcePath.hpp"
#include "ScreenManager.h"

GameObject::GameObject(std::string path, Vector2f pos) : pos(pos)
{
    if(!texture.loadFromFile(path))
        std::cout << "Can't load mapObject " << path << std::endl;
    
    sprite.setTexture(texture);
    sprite.setPosition(pos.x, pos.y);
    isUse = false;
    
    if(!buf.loadFromFile(resourcePath() + "potion.wav"))
        std::cout << "Can't load sound potion" << std::endl;
    
    sound.setBuffer(buf);
    
    std::cout << "Added gameObject at " << pos.x << "/" << pos.y << std::endl;
}

GameObject::~GameObject()
{}

void GameObject::update(float dt)
{
    sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 10*dt);
    if(sprite.getPosition().y < 0)
        isUse = true;
}

void GameObject::effect(Entity *target)
{
    isUse = true;
    sound.play();
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
    GameObject::effect(target);
    target->getFighterCharacteristics().addHealth(400);
    text = "+400 Health";
}

GameObjectStrength::GameObjectStrength(Vector2f pos) : GameObject(resourcePath() + "potionStrength.png", pos)
{
}

void GameObjectStrength::effect(Entity *target)
{
    GameObject::effect(target);
    target->getFighterCharacteristics().addStrength(50);
    text = "+50 Strength";
}

GameObjectEnergy::GameObjectEnergy(Vector2f pos) : GameObject(resourcePath() + "potionEnergy.png", pos)
{
}

void GameObjectEnergy::effect(Entity *target)
{
    GameObject::effect(target);
    target->getFighterCharacteristics().getBlockState().addActiveCooldown(.2f);
    text = "+0.2 Block time";
}


GameObjectKey::GameObjectKey(ScreenManager *sm, Vector2f pos) : GameObject(resourcePath() + "potionKey.png", pos), sm(sm)
{
}

void GameObjectKey::effect(Entity *target)
{
    GameObject::effect(target);
    sm->nextScene();
    //text = "Key !";
}

Vector2f GameObject::getPos()
{
    return sprite.getPosition();
}

String GameObject::getString()
{
    return text;
}