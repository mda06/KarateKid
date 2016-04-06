//
//  ScenarioScreen.cpp
//  KarateKid
//
//  Created by Timothy Van Peteghem on 6/04/16.
//  Copyright © 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "ScenarioScreen.h"
#include "ScreenManager.h"
#include "ResourcePath.hpp"
#include <iostream>

ScenarioScreen::ScenarioScreen(RenderWindow *w, ScreenManager *sm, std::string img) : AbstractScreen(sm)
{
    if(!txt.loadFromFile(resourcePath() + img))
        std::cout << "Can't load scenario texture" << std::endl;
    spr.setTexture(txt);
    
    spr.scale(w->getSize().x / spr.getGlobalBounds().width, w->getSize().y / spr.getGlobalBounds().height);
    //if(!font.loadFromFile(resourcePath() + "master_of_break.ttf"))
        //std::cout << "Can't load font !" << std::endl;
}

void ScenarioScreen::handleInput(sf::Event &event)
{
    if(event.type == Event::KeyPressed)
    {
        screenManager->setNextScenarioScreen();
    }
}


void ScenarioScreen::update(sf::Time time)
{}

void ScenarioScreen::render(RenderTarget &rt)
{
    rt.draw(spr);
}