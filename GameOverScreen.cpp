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
    if(!txtGameOver.loadFromFile(resourcePath() + "gameOver.jpg"))
        std::cout << "Can't load game over texture" << std::endl;
    sprGameOver.setTexture(txtGameOver);
}

void GameOverScreen::handleInput(sf::Event &event)
{
    if(event.type == Event::KeyPressed)
    {
        screenManager->initScenes();
        screenManager->setScreen("menulost");
    }
}

void GameOverScreen::update(sf::Time time)
{}

void GameOverScreen::render(RenderTarget &rt)
{
    rt.draw(sprGameOver);
}