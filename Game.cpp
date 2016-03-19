//
//  Game.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 29/02/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "Game.h"
#include "ResourcePath.hpp"
#include "GameOverScreen.h"

Game::Game() : window(VideoMode(640, 480), "Karate Kid 1984"/*, Style::Titlebar | Style::Close*/)

{
    screenManager = new ScreenManager();
    Scene *s = new Scene(screenManager, resourcePath() + "forest.txt", "forest.tmx", Vector2f(40, 30));
    s->init();
    screenManager->addScreen(s, "sceneforest");
    screenManager->addScreen(new GameOverScreen(screenManager), "gameover");
    screenManager->addScreen(new MenuScreen(screenManager, &window), "menu");
    
}

Game::~Game()
{
    delete screenManager;
}

void Game::run()
{
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
                   if(screenManager->getCurrentScreenKey() == "sceneforest")
                       screenManager->setScreen("menu");
                   else
                       screenManager->setScreen("sceneforest");
                        
                }
          
            screenManager->handleInput(event);
        }
     
        screenManager->update(ellapsed);
        
        window.clear();
        screenManager->render(window);
        window.display();
    }
}