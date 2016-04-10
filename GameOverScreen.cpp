//
//  GameOverScreen.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 19/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "GameOverScreen.h"
#include "ScreenManager.h"
#include "ResourcePath.hpp"
#include <iostream>

GameOverScreen::GameOverScreen(ScreenManager *sm) : AbstractScreen(sm)
{
    /*
    if(!txtGameOver.loadFromFile(resourcePath() + "gameOver.jpg"))
        std::cout << "Can't load game over texture" << std::endl;
    sprGameOver.setTexture(txtGameOver);
    */
    
    if(!font.loadFromFile(resourcePath() + "master_of_break.ttf"))
        std::cout << "Can't load font !" << std::endl;
    
    game.setFont(font);
    game.setCharacterSize(120);
    game.setString("Game");
    game.setPosition(320 - game.getGlobalBounds().width / 2, 170 - game.getGlobalBounds().height / 2);
    
    over.setFont(font);
    over.setCharacterSize(120);
    over.setString("Over");
    over.setPosition(320 - over.getGlobalBounds().width / 2, 310 - over.getGlobalBounds().height / 2);
}

void GameOverScreen::handleInput(sf::Event &event)
{
    if(event.type == Event::KeyPressed)
    {
        screenManager->setScreen("menulost");
    }
}

void GameOverScreen::update(sf::Time time)
{}

void GameOverScreen::render(RenderTarget &rt)
{
    //rt.draw(sprGameOver);
    rt.draw(game);
    rt.draw(over);
}