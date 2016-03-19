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
    if(!txtWin.loadFromFile(resourcePath() + "winScreenBG.png"))
        std::cout << "Can't load win texture" << std::endl;
    sprWin.setTexture(txtWin);
}

void WinScreen::handleInput(sf::Event &event)
{
    if(event.type == Event::KeyPressed)
    {
        screenManager->initScenes();
        screenManager->setScreen("menu");
    }
}

void WinScreen::update(sf::Time time)
{}

void WinScreen::render(RenderTarget &rt)
{
    rt.draw(sprWin);
}