//
//  GUIBar.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 7/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "GUIBar.h"
#include <iostream>

GUIBar::GUIBar(std::string pathBack, std::string pathFront, Vector2f pos, int mw, bool wb) : withBack(wb), maxWidth(mw)
{
    if(!textBack.loadFromFile(pathBack))
        std::cout << "Error texture " << pathBack << " not found." << std::endl;
    if(!textFront.loadFromFile(pathFront))
        std::cout << "Error texture " << pathFront << " not found." << std::endl;
   
    IntRect irBack;
    irBack.height = 18;
    irBack.width = 152;
    irBack.top = 0;
    irBack.left = 0;
    spriteBack.setTexture(textBack);
    spriteBack.setTextureRect(irBack);
    spriteBack.setPosition(pos);
    
    irFront.height = 7;
    irFront.width = maxWidth;
    irFront.top = 0;
    irFront.left = 0;
    spriteFront.setTexture(textFront);
    spriteFront.setTextureRect(irFront);
    
    if(!withBack)
    {
        spriteFront.setScale(0.5, 1);
        spriteFront.setPosition(pos.x - (maxWidth / 4), pos.y - 30);
    }
    else
        spriteFront.setPosition(pos.x + 22, pos.y + 5);
}

void GUIBar::setPerc(float perc)
{
    irFront.width = perc * maxWidth;
    spriteFront.setTextureRect(irFront);
}

void GUIBar::setWithBack(bool b)
{
    withBack = b;
    spriteFront.setScale(.5, 1);
}

void GUIBar::setPosition(Vector2f pos)
{
    spriteFront.setPosition(pos.x - (maxWidth / 4), pos.y - 30);
}

void GUIBar::draw(RenderTarget &rt)
{
    if(withBack)
        rt.draw(spriteBack);
    rt.draw(spriteFront);
}