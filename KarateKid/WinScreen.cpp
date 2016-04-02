//
//  WinScreen.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 19/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "WinScreen.h"
#include "ScreenManager.h"
#include "ResourcePath.hpp"
#include <iostream>

WinScreen::WinScreen(ScreenManager *sm) : AbstractScreen(sm)
{
    /*
    if(!txtWin.loadFromFile(resourcePath() + "winScreenBG.png"))
        std::cout << "Can't load win texture" << std::endl;
    sprWin.setTexture(txtWin);
    */
    
    if(!font.loadFromFile(resourcePath() + "master_of_break.ttf"))
        std::cout << "Can't load font !" << std::endl;
    
    text1.setFont(font);
    text1.setCharacterSize(100);
    text1.setString("Level");
    text1.setPosition(320 - text1.getGlobalBounds().width / 2, 170 - text1.getGlobalBounds().height / 2);
    
    text2.setFont(font);
    text2.setCharacterSize(100);
    text2.setString("Completed");
    text2.setPosition(320 - text2.getGlobalBounds().width / 2, 310 - text2.getGlobalBounds().height / 2);
}

void WinScreen::handleInput(sf::Event &event)
{
    if(event.type == Event::KeyPressed)
    {
        if(screenManager->getSceneCount() < 3)
            screenManager->setScreen("menuwon");
        else
            screenManager->setScreen("end");
    }
}


void WinScreen::update(sf::Time time)
{}

void WinScreen::render(RenderTarget &rt)
{
    //rt.draw(sprWin);
    rt.draw(text1);
    rt.draw(text2);
}