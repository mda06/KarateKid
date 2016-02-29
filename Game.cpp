//
//  Game.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 29/02/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "Game.h"
#include "ResourcePath.hpp"
#include <iostream>

Game::Game() : window(VideoMode(640, 480), "Karate Kid 1984"), ml(resourcePath())
{
    
}

void Game::run()
{
    init();
    
    Clock clock;
    
    while (window.isOpen())
    {
        Time ellapsed = clock.restart();
        while (window.pollEvent(event))
        {
            handleInput();
        }
     
        update(ellapsed.asSeconds());
        render();
    }
}

void Game::init()
{
    ml.Load("testmap.tmx");
}

void Game::handleInput()
{
    // Close window: exit
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    
    // Escape pressed: exit
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        window.close();
    }

}

void Game::update(float dt)
{
}

void Game::render()
{
    window.clear();
    window.draw(ml);
    window.display();
}