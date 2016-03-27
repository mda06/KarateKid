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

MenuScreen::MenuScreen(ScreenManager *sm, Window *w, MenuState state) : AbstractScreen(sm), renderHowToPlay(false), btnPlay(Vector2f(320, 180), resourcePath() + "btnBgWhite.png", "Play"), btnHowTo(Vector2f(320, 260), resourcePath() + "btnBgWhite.png", "How"), btnReturn(Vector2f(550, 340), resourcePath() + "btnBg.png", "Return"), btnExit(Vector2f(320, 340), resourcePath() + "btnBgWhite.png", "Exit"), firstIndex(1), lastIndex(3), index(1), focus(false), state(state)
{
    if(!textHowToPlay.loadFromFile(resourcePath() + "HowToPlay.png"))
        std::cout << "Can't load howtoplay.png" << std::endl;
    
    textHowToPlay.setSmooth(true);
    sprHowToPlay.setTexture(textHowToPlay);
    
    if(!textBG.loadFromFile(resourcePath() + "menu-bg.jpg"))
        std::cout << "Can't load menu-BG" << std::endl;

    textBG.setSmooth(true);
    sprBG.setTexture(textBG);

    sprBG.scale(w->getSize().x / sprBG.getLocalBounds().width, w->getSize().y / sprBG.getLocalBounds().height);
    
    if(!font.loadFromFile(resourcePath() + "master_of_break.ttf"))
        std::cout << "Can't load font !" << std::endl;
    text.setFont(font);
    text.setCharacterSize(40);
    text.setColor(Color::White);

    switch (state)
    {
        case BEGIN:
            text.setString("Karate Kid");
            btnPlay.setText("Play");
            break;
        case PAUSE:
            text.setString("Pause");
            btnPlay.setText("Continue");
            break;
        case WON:
            text.setString("Wel done ! Let's try next level.");
            btnPlay.setText("Next");
            break;
        case LOST:
            btnPlay.setText("Retry");
            text.setString("You lost, want to try again ?");
            break;
    }

    text.setPosition(320 - text.getGlobalBounds().width / 2, 80 - text.getGlobalBounds().height / 2);
    
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
                focus = true;
                event.key.code = sf::Keyboard::Key::Return;
            }
            else focus = false;
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            if(btnReturn.getSprite().getGlobalBounds().contains(Vector2f(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)))
                focus = true;
            else focus = false;
        }
        
        btnReturn.handleInput(event, focus);
    }
    else
    {
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
        }
        else if(event.type == Event::MouseMoved)
        {
            if(btnPlay.getSprite().getGlobalBounds().contains(Vector2f(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)))
                index = 1;
            else if(btnHowTo.getSprite().getGlobalBounds().contains(Vector2f(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)))
                index = 2;
            else if(btnExit.getSprite().getGlobalBounds().contains(Vector2f(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y)))
                index = 3;
            else index = 0;
        }
        
        btnPlay.handleInput(event, (index == 1));
        btnHowTo.handleInput(event, (index == 2));
        btnExit.handleInput(event, (index == 3));
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
    {
        init();
        renderHowToPlay = true;
    }
    if(btnExit.clicked())
        window->close();
    if(btnPlay.clicked())
    {
        switch (state)
        {
            case BEGIN:
                screenManager->setScreen("sceneforest");
                break;
            case PAUSE:
                screenManager->setScreen(oldScreenKey);
                break;
            case WON:
                screenManager->setScreen("scenedesert");
                break;
            case LOST:
                screenManager->setScreen("sceneforest");
                break;
        }
    }
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
        rt.draw(text);
        btnPlay.render(rt);
        btnHowTo.render(rt);
        btnExit.render(rt);
    }
}

void MenuScreen::enter(std::string osk)
{
    oldScreenKey = osk;
    std::cout << "osk: " << osk << std::endl;
    init();
}

void MenuScreen::init()
{
    index = 1;
    
    btnPlay.setScale(1.2f, 1.2f);
    btnHowTo.setScale(1, 1);
    btnExit.setScale(1, 1);
    btnReturn.setScale(1, 1);
    focus = false;
}