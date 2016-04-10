//
//  EndScreen.cpp
//  KarateKid
//
//  Created by Timothy Van Peteghem on 28/03/16.
//  Copyright © 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "EndScreen.h"
#include "ScreenManager.h"
#include "ResourcePath.hpp"
#include <iostream>

EndScreen::EndScreen(ScreenManager *sm) : AbstractScreen(sm)
{
    /*
    if(!txtEnd.loadFromFile(resourcePath() + "theend.png"))
        std::cout << "Can't load win texture" << std::endl;
    sprEnd.setTexture(txtEnd);
     */
    if(!font.loadFromFile(resourcePath() + "master_of_break.ttf"))
        std::cout << "Can't load font !" << std::endl;
    text.setFont(font);
    text.setCharacterSize(125);
    text.setString("The End !");
    text.setPosition(370 - text.getGlobalBounds().width / 2, 240 - text.getGlobalBounds().height / 2);
}

void EndScreen::handleInput(sf::Event &event)
{
    if(event.type == Event::KeyPressed)
    {
        screenManager->setScreen("menubegin");
    }
}

void EndScreen::update(sf::Time time)
{}

void EndScreen::render(RenderTarget &rt)
{
    //rt.draw(sprEnd);
    rt.draw(text);
}