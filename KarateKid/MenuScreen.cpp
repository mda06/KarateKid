//
//  MenuScreen.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 14/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "MenuScreen.h"
#include "ScreenManager.h"
#include "ResourcePath.hpp"
#include <iostream>

MenuScreen::MenuScreen(ScreenManager *sm, Window *w) : AbstractScreen(sm), renderHowToPlay(false), btnPlay(Vector2f(320, 180), resourcePath() + "btnBg.png", "Play"), btnExit(Vector2f(320, 260), resourcePath() + "btnBg.png", "Exit"), btnHowTo(Vector2f(320, 340), resourcePath() + "btnBg.png", "How"), btnReturn(Vector2f(550, 340), resourcePath() + "btnBg.png", "Return"), firstIndex(1), lastIndex(3), index(1)
{
    if(!textHowToPlay.loadFromFile(resourcePath() + "HowToPlay.png"))
        std::cout << "Can't load howtoplay.png" << std::endl;
    
    textHowToPlay.setSmooth(true);
    sprHowToPlay.setTexture(textHowToPlay);
    
    if(!textBG.loadFromFile(resourcePath() + "menuScreenBG.png"))
        std::cout << "Can't load menuScreenBG" << std::endl;
    
    textBG.setSmooth(true);
    sprBG.setTexture(textBG);
    
    window = w;
 }

void MenuScreen::handleInput(sf::Event &event)
{
    if(renderHowToPlay)
    {
        if(event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Key::BackSpace || event.key.code == sf::Keyboard::Key::Escape)
            {
                renderHowToPlay = false;
                index = 1;
                btnPlay.setScale(1.2f, 1.2f);
                return;
            }
        }
        
        btnReturn.handleInput(event, Vector2f(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y));
        return;
    }
    
    if(event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Key::Down)
        {
            if (index < lastIndex)
                index++;
            else
                index = firstIndex;
        }
        else if (event.key.code == sf::Keyboard::Key::Up)
        {
            if (index > firstIndex)
                index--;
            else
                index = lastIndex;
        }
        else if (event.key.code == sf::Keyboard::Key::Return)
        {
            btnPlay.handleInput(event,false);
            btnExit.handleInput(event, false);
            btnHowTo.handleInput(event, false);
        }

        
        switch (index)
        {
            case 1:
                btnPlay.handleInput(event, true);
                btnExit.handleInput(event, false);
                btnHowTo.handleInput(event, false);
                break;
            case 2:
                btnPlay.handleInput(event,false);
                btnExit.handleInput(event, true);
                btnHowTo.handleInput(event, false);
                break;
            case 3:
                btnPlay.handleInput(event,false);
                btnExit.handleInput(event, false);
                btnHowTo.handleInput(event, true);
                break;
        }
    }
    else
    {
        btnPlay.handleInput(event, Vector2f(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y));
        btnExit.handleInput(event, Vector2f(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y));
        btnHowTo.handleInput(event, Vector2f(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y));
    }
}

void MenuScreen::update(Time time)
{
    if(renderHowToPlay)
    {
        if(btnReturn.clicked())
            renderHowToPlay = false;
        return;
    }
    if(btnHowTo.clicked())
        renderHowToPlay = true;
    if(btnExit.clicked())
        window->close();
    if(btnPlay.clicked())
        screenManager->setScreen("sceneforest");
}

void MenuScreen::render(RenderTarget &rt)
{
    
    if(renderHowToPlay)
    {
        rt.draw(sprHowToPlay);
        btnReturn.render(rt);
    }
    else
    {
        rt.draw(sprBG);
        btnPlay.render(rt);
        btnExit.render(rt);
        btnHowTo.render(rt);
    }
}

void MenuScreen::enter()
{
    index = 1;
    
    btnPlay.setScale(1.2f, 1.2f);
}