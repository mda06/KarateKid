//
//  Player.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 8/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "Player.h"
#include "ResourcePath.hpp"

//Call gbHealth true/false
Player::Player(Vector2f pos, Vector2f size) : Entity(pos, size, true, 1500, 100, 1, .6f, .6f, false), gbEnergy(resourcePath() + "barre_energie_vide.png", resourcePath() + "barre_energie_couleur.png", Vector2f(10, 100), 126, true), gbStrength(resourcePath() + "barre_force_vide.png", resourcePath() + "barre_force_couleur.png", Vector2f(10, 130), 126, true)
{
    //TODO: change this !
    if(size.y >= 100){
        float sc = size.y / 80;
        accel = Vector2f(1000, 500) * sc;
        deccel = Vector2f(850, 1000) * sc;
        maxVel = Vector2f(400, 450) * sc;
    }
}

void Player::init(CollisionHandler *ch, Vector2f size, Vector2f pos)
{
    //TODO: change this !
    if(size.y >= 100){
        float sc = size.y / 80;
        accel = Vector2f(1000, 500) * sc;
        deccel = Vector2f(850, 1000) * sc;
        maxVel = Vector2f(400, 450) * sc;
    }

    setColHandler(ch);
    
    /*
    Vector2f scale = Vector2f(size.x / getFeatureHandler().getSprite().getGlobalBounds().width, size.y / getFeatureHandler().getSprite().getGlobalBounds().height);
    Vector2f oldSize = Vector2f(getFeatureHandler().getSprite().getGlobalBounds().width, getFeatureHandler().getSprite().getGlobalBounds().height);
    Vector2f newSize = Vector2f(oldSize.x * scale.x, oldSize.y * scale.y);
    
    getFeatureHandler().getSprite().setScale(scale);
    Vector2f realSize = Vector2f(getFeatureHandler().getSprite().getGlobalBounds().width, getFeatureHandler().getSprite().getGlobalBounds().height);
    */
    
    setPosition(pos);
    featureHandler.setSize(size);
    /*
    std::cout << "p set correctly in scene" << std::endl << "- asked size = " << size.x << ", " << size.y << std::endl << "- scale : " << scale.x << ", " << scale.y << std::endl << "- oldsize : " << oldSize.x << ", " << oldSize.y << std::endl << "- newsize : " << newSize.x << ", " << newSize.y << std::endl<< "- realsize : " << realSize.x << ", " << realSize.y << std::endl;
    */
    
    std::cout << "init player" << std::endl;
    direction = STOP;
    vel = Vector2f();
    featureHandler.getSprite().setPosition(initialPos);
    if(!featureHandler.getEnemy())
        std::cout << "player set pos to " << initialPos.x << ", " << initialPos.y << std::endl;
    featureHandler.init();
}

void Player::updateGUIBar()
{
    Entity::updateGUIBar();
    FighterCharacteristics fc = getFighterCharacteristics();
    gbEnergy.setPerc((float)fc.getBlockState().getCurActiveCooldown() / fc.getBlockState().getActiveCooldown());
    gbStrength.setPerc((float)fc.getCurrStrength() / (float)fc.getMaxStrength());
}

void Player::drawEnergyBar(RenderTarget &rt)
{
    gbEnergy.draw(rt);
}

void Player::drawStrengthBar(RenderTarget &rt)
{
    gbStrength.draw(rt);
}