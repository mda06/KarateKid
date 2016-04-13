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

MenuScreen::MenuScreen(ScreenManager *sm, RenderWindow *w, MenuState state) : AbstractScreen(sm), renderHowToPlay(false), btnPlay(Vector2f(320, 180), resourcePath() + "buttonbg.png", "Play"), btnHowTo(Vector2f(320, 260), resourcePath() + "buttonbg.png", "Help"), btnReturn(Vector2f(100, 50), resourcePath() + "buttonbg_small.png", "Return"), btnExit(Vector2f(320, 340), resourcePath() + "buttonbg.png", "Exit"), btnNext(Vector2f(510, 50), resourcePath() + "buttonbg_arrowright.png", "Controls"), firstIndex(1), lastIndex(3), index(1), state(state), renderControls(false)
{
    if(!txtrInstructions.loadFromFile(resourcePath() + "Instructions.png"))
        std::cout << "Can't load instructions.png" << std::endl;
    if(!txtrControls.loadFromFile(resourcePath() + "Controls.png"))
        std::cout << "Can't load controls.png" << std::endl;
    
    txtrInstructions.setSmooth(true);
    sprInstructions.setTexture(txtrInstructions);
    txtrControls.setSmooth(true);
    sprControls.setTexture(txtrControls);
    
    if(!textBG.loadFromFile(resourcePath() + "menu-bg.jpg"))
        std::cout << "Can't load menu-BG" << std::endl;

    textBG.setSmooth(true);
    sprBG.setTexture(textBG);

    sprBG.scale(w->getSize().x / sprBG.getLocalBounds().width, w->getSize().y / sprBG.getLocalBounds().height);
    
    if(!font.loadFromFile(resourcePath() + "master_of_break.ttf"))
        std::cout << "Can't load font !" << std::endl;
    textMenu.setFont(font);
    textMenu.setCharacterSize(40);
    textMenu.setColor(Color::White);
    
    textControls.setFont(font);
    textControls.setCharacterSize(40);
    textControls.setColor(Color::White);
    textControls.setString("Controls");
                               
    textInstructions.setFont(font);
    textInstructions.setCharacterSize(40);
    textInstructions.setColor(Color::White);
    textInstructions.setString("Instructions");

    switch (state)
    {
        case BEGIN:
            textMenu.setString("Karate Kid");
            btnPlay.setText("Start");
            break;
        case PAUSE:
            textMenu.setString("Pause");
            btnPlay.setText("Continue");
            break;
        case WON:
            textMenu.setString("Wel done ! Let's try next level.");
            btnPlay.setText("Next");
            break;
        case LOST:
            btnPlay.setText("Retry");
            textMenu.setString("You lost, want to try again ?");
            break;
    }

    textMenu.setPosition(320 - textMenu.getGlobalBounds().width / 2, 60 - textMenu.getGlobalBounds().height / 2);
    textControls.setPosition(320 - textControls.getGlobalBounds().width / 2, 60 - textControls.getGlobalBounds().height / 2);
    textInstructions.setPosition(320 - textInstructions.getGlobalBounds().width / 2, 60 - textInstructions.getGlobalBounds().height / 2);
    
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
                index = 1;
                event.key.code = sf::Keyboard::Key::Return;
            }
            if (event.key.code == sf::Keyboard::Key::Left || event.key.code == sf::Keyboard::Key::Right)
            {
                index = 2;
                event.key.code = sf::Keyboard::Key::Return;
            }
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            if(btnReturn.getSprite().getGlobalBounds().contains(window->mapPixelToCoords(Mouse::getPosition(*window))))
                index = 1;
            else if(btnNext.getSprite().getGlobalBounds().contains(window->mapPixelToCoords(Mouse::getPosition(*window))))
                index = 2;
            else index = 0;
        }
        
        btnReturn.handleInput(event, index == 1);
        btnNext.handleInput(event, index == 2);
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
            if(btnPlay.getSprite().getGlobalBounds().contains(window->mapPixelToCoords(Mouse::getPosition(*window))))
                index = 1;
            else if(btnHowTo.getSprite().getGlobalBounds().contains(window->mapPixelToCoords(Mouse::getPosition(*window))))
                index = 2;
            else if(btnExit.getSprite().getGlobalBounds().contains(window->mapPixelToCoords(Mouse::getPosition(*window))))
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
        {
            init();
            renderHowToPlay = false;
        }
        if(btnNext.clicked())
        {
            init();
            changeBtnNextText();
            index = 0;
            if(renderControls)
                renderControls = false;
            else
                renderControls = true;
        }
        
        return;
    }
    if(btnHowTo.clicked())
    {
        init();
        renderHowToPlay = true;
        renderControls = false;
    }
    if(btnExit.clicked())
        window->close();
    if(btnPlay.clicked())
    {
        switch (state)
        {
            case BEGIN:
                screenManager->setSceneCount(1);
                screenManager->setScenarioScreen(1);
                break;
            case PAUSE:
            case WON:
            case LOST:
                screenManager->setScene(screenManager->getSceneCount());
                break;
        }
    }
}

void MenuScreen::render(RenderTarget &rt)
{
    
    if(renderHowToPlay)
    {
        if(renderControls)
        {
            rt.draw(sprControls);
            rt.draw(textControls);
        }
        else
        {
            rt.draw(sprInstructions);
            rt.draw(textInstructions);
        }
        
        btnReturn.render(rt);
        btnNext.render(rt);
    }
    else
    {
        rt.draw(sprBG);
        rt.draw(textMenu);
        btnPlay.render(rt);
        btnHowTo.render(rt);
        btnExit.render(rt);
    }
}

void MenuScreen::enter()
{
    init();
}

void MenuScreen::init()
{
    index = 1;
    
    btnPlay.setScale(1.2f, 1.2f);
    btnHowTo.setScale(1, 1);
    btnExit.setScale(1, 1);
    btnReturn.setScale(1, 1);
    btnNext.setScale(1, 1);
}

void MenuScreen::changeBtnNextText()
{
    if(btnNext.getText() == "Controls")
        btnNext.setText("Instructions");
    else if(btnNext.getText() == "Instructions")
        btnNext.setText("Controls");
    else
        btnNext.setText("Next");
}