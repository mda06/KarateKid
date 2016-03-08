//
//  Game.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 29/02/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "Game.h"
#include "ResourcePath.hpp"

Game::Game() : window(VideoMode(640, 480), "Karate Kid 1984"), scene(resourcePath() + "forest.txt", "forest.tmx", Vector2f(40, 430))
{}

void Game::run()
{
    scene.init();
    
    Clock clock;
    Event event;
    
    while (window.isOpen())
    {
        Time ellapsed = clock.restart();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            window.close();
            scene.handleInput(event);
        }
     
        scene.update(ellapsed);
        window.clear();
        scene.render(window);
        window.display();
    }
}