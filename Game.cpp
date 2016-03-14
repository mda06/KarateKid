//
//  Game.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 29/02/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "Game.h"
#include "ResourcePath.hpp"

Game::Game() : window(VideoMode(640, 480), "Karate Kid 1984"/*, Style::Titlebar | Style::Close*/), scene(resourcePath() + "forest.txt", "forest.tmx", Vector2f(40, 30)), renderMenuScreen(true), menuScreen(&window)

{
}

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
            if(event.type == sf::Event::Closed) window.close();
            if(event.type == Event::KeyReleased)
                if(event.key.code == Keyboard::Escape)
                {
                    renderMenuScreen = !renderMenuScreen;
                    if(renderMenuScreen)
                        menuScreen.setGoToPlay(false);
                }
          
            if(renderMenuScreen)
                menuScreen.handleInput(event);
            else
                scene.handleInput(event);
        }
     
        if(renderMenuScreen)
            menuScreen.update(ellapsed.asSeconds());
        else
            scene.update(ellapsed);
        
        if(menuScreen.goToPlay())
            renderMenuScreen = false;
        
        window.clear();
        if(renderMenuScreen)
            menuScreen.render(window);
        else
            scene.render(window);
        window.display();
    }
}