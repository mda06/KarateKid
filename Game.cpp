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
#include "WinScreen.h"
#include "MenuScreen.h"
#include "EndScreen.h"

Game::Game() : window(VideoMode(640, 480), "Karate Kid 1984"/*, Style::Titlebar | Style::Close*/)
{
    screenManager = new ScreenManager();
    
    Scene *s = new Scene(&window, screenManager, resourcePath() + "forest.txt", "forest.tmx", Vector2f(40, 30), Vector2f(48, 48));
    s->init();
    screenManager->addScreen(s, "sceneforest");
    
    s = new Scene(&window, screenManager, resourcePath() + "desert.txt", "desert.tmx", Vector2f(120, 650), Vector2f(80, 100));
    s->init();
    screenManager->addScreen(s, "scenedesert");
    
    s = new Scene(&window, screenManager, resourcePath() + "beach.txt", "beach.tmx", Vector2f(40, 80), Vector2f(48, 48));
    s->init();
    screenManager->addScreen(s, "scenebeach");
    
    s = new Scene(&window, screenManager, resourcePath() + "final.txt", "final.tmx", Vector2f(80, 363), Vector2f(100, 100), true);
    s->init();
    screenManager->addScreen(s, "scenefinal");
    
    screenManager->addScreen(new GameOverScreen(screenManager), "gameover");
    screenManager->addScreen(new WinScreen(screenManager), "win");
    screenManager->addScreen(new EndScreen(screenManager), "end");
    screenManager->addScreen(new MenuScreen(screenManager, &window, MenuScreen::BEGIN), "menubegin");
    screenManager->addScreen(new MenuScreen(screenManager, &window, MenuScreen::PAUSE), "menupause");
    screenManager->addScreen(new MenuScreen(screenManager, &window, MenuScreen::WON), "menuwon");
    screenManager->addScreen(new MenuScreen(screenManager, &window, MenuScreen::LOST), "menulost");
    
    screenManager->setScreen("menubegin");
    
    oldCurrScreenKey = "sceneforest";
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
        //Bug when resing the window, the time that we drag will increase ellapsed and the player get than a to big delta value for the formulas...
        if(ellapsed.asSeconds() > .005f)
            ellapsed = clock.restart();
        
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
            if(event.type == Event::KeyReleased)
            {
                if(event.key.code == Keyboard::Escape)
                {
                    if(screenManager->getCurrentScreenKey() == "menupause")
                        screenManager->setScreen(oldCurrScreenKey);
                    else
                    {
                        oldCurrScreenKey = screenManager->getCurrentScreenKey();
                        screenManager->setScreen("menupause");
                    }
                }
                if(event.key.code == Keyboard::Num1)
                {
                    if(screenManager->getCurrentScreenKey() != "sceneforest")
                    {
                        screenManager->setScreen("sceneforest");
                        screenManager->setSceneCount(1);
                    }
                }
                if(event.key.code == Keyboard::Num2)
                {
                    if(screenManager->getCurrentScreenKey() != "scenedesert")
                    {
                        screenManager->setScreen("scenedesert");
                        screenManager->setSceneCount(2);
                    }
                }
                if(event.key.code == Keyboard::Num3)
                {
                    if(screenManager->getCurrentScreenKey() != "scenebeach")
                    {
                        screenManager->setScreen("scenebeach");
                        screenManager->setSceneCount(3);
                    }
                }
                if(event.key.code == Keyboard::Num4)
                {
                    if(screenManager->getCurrentScreenKey() != "scenefinal")
                    {
                        screenManager->setScreen("scenefinal");
                        screenManager->setSceneCount(4);
                    }
                }
                if(event.key.code == Keyboard::Num0)
                {
                    screenManager->setScreen("end");
                }
                if(event.key.code == Keyboard::Num9)
                {
                    screenManager->setScreen("win");
                }
            }
          
            screenManager->handleInput(event);
        }
        
        screenManager->update(ellapsed);
        
        window.clear();
        screenManager->render(window);
        window.display();
    }
}