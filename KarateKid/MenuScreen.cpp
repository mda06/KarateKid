//
//  MenuScreen.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 14/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "MenuScreen.h"
#include "ResourcePath.hpp"
#include <iostream>

MenuScreen::MenuScreen(Window *w): renderHowToPlay(false), btnPlay(Vector2f(320, 180), resourcePath() + "btnBg.png", "Play"), btnExit(Vector2f(320, 260), resourcePath() + "btnBg.png", "Exit"), btnHowTo(Vector2f(320, 340), resourcePath() + "btnBg.png", "How"), btnReturn(Vector2f(550, 340), resourcePath() + "btnBg.png", "Return")
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
        btnReturn.handleInput(event, Vector2f(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y));
        return;
    }
    
    btnPlay.handleInput(event, Vector2f(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y));
    btnExit.handleInput(event, Vector2f(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y));
    btnHowTo.handleInput(event, Vector2f(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y));
}

void MenuScreen::update(float dt)
{
    if(renderHowToPlay)
    {
        if(btnReturn.clicked())
            renderHowToPlay = false;
        return;
    }
    if(btnPlay.clicked())
        play = true;
    if(btnHowTo.clicked())
        renderHowToPlay = true;
    if(btnExit.clicked())
        window->close();
}

void MenuScreen::setGoToPlay(bool b)
{
    play = b;
}

bool MenuScreen::goToPlay()
{
    return play;
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