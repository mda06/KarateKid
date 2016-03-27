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
    text.setPosition(pos.x - text.getGlobalBounds().width / 2, pos.y - text.getGlobalBounds().height / 2);
    
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

void SimpleButton::handleInput(Event &event, bool focus)
{
    if(event.type == Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Key::Return || event.key.code == sf::Keyboard::Key::Space)
        {
            if (focus)
                isClicked = true;
            sprBg.setScale(1, 1);
        }
        else if (event.key.code == sf::Keyboard::Key::Up || event.key.code == sf::Keyboard::Key::Down)
        {
            if (focus)
                sprBg.setScale(1.2f, 1.2f);
            else
                sprBg.setScale(1, 1);
        }
    }
    else if (event.type == Event::MouseMoved)
    {
        if (focus)
            sprBg.setScale(1.2f, 1.2f);
        else
            sprBg.setScale(1, 1);
    }
    else if (Mouse::isButtonPressed(Mouse::Button::Left))
    {
        if (focus)
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

void SimpleButton::setScale(float x, float y)
{
    sprBg.setScale(x, y);
}

Sprite SimpleButton::getSprite()
{
    return sprBg;
}

void SimpleButton::setText(std::string txt)
{
    text.setString(txt);
    text.setPosition(sprBg.getPosition().x - text.getGlobalBounds().width / 2, sprBg.getPosition().y - text.getGlobalBounds().height / 2);
}