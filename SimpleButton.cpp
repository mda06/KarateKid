//
//  SimpleButton.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 14/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "SimpleButton.h"
#include "ResourcePath.hpp"
#include <iostream>

SimpleButton::SimpleButton(Vector2f pos, std::string path, std::string txt)
{
    if(!textBg.loadFromFile(path))
        std::cout << "Can't load button bg" << std::endl;
    
    textBg.setSmooth(true);
    sprBg.setTexture(textBg);
    sprBg.setOrigin(sprBg.getGlobalBounds().width / 2, sprBg.getGlobalBounds().height / 2);
    sprBg.setPosition(pos);
    
    if(!font.loadFromFile(resourcePath() + "master_of_break.ttf"))
        std::cout << "Can't load font !" << std::endl;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setColor(Color::Black);
    text.setString(txt);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(pos.x, pos.y + 5);
    
    isClicked = false;
}

void SimpleButton::handleInput(Event &event, Vector2f mousePos)
{
    if(event.type == Event::MouseMoved)
    {
        FloatRect fr = sprBg.getGlobalBounds();
        if(fr.contains(mousePos))
           sprBg.setScale(1.2f, 1.2f);
        else
           sprBg.setScale(1, 1);
    }
    if(Mouse::isButtonPressed(Mouse::Button::Left))
    {
        FloatRect fr = sprBg.getGlobalBounds();
        if(fr.contains(mousePos))
            isClicked = true;
    }
}

bool SimpleButton::clicked()
{
    if(isClicked)
    {
        isClicked = false;
        return true;
    }
    return false;
}

void SimpleButton::render(sf::RenderTarget &rt)
{
    rt.draw(sprBg);
    rt.draw(text);
}