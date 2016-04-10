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
}

void Player::initToScene(CollisionHandler *ch, Vector2f size, Vector2f pos)
{
    //TODO: change this !
    if(size.y >= 100){
        float sc = size.y / 80;
        accel = Vector2f(1000, 500) * sc;
        deccel = Vector2f(850, 1000) * sc;
        maxVel = Vector2f(400, 450) * sc;
    }

    setColHandler(ch);
    setPosition(pos);
    featureHandler.setSize(size);
    
    direction = STOP;
    vel = Vector2f();
    featureHandler.getSprite().setPosition(initialPos);
}

void Player::initStats()
{
    Entity::init();
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