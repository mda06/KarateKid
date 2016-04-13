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
#include "ScenarioScreen.h"

Game::Game() : window(VideoMode(640, 480), "Karate Kid 1984"/*, Style::Titlebar | Style::Close*/)
{
    screenManager = new ScreenManager();
    player = new Player(Vector2f(0, 0), Vector2f(48, 48));
    
    Scene *s = new Scene(player, &window, screenManager, resourcePath() + "forest.txt", "forest.tmx", Vector2f(40, 30), Vector2f(48, 48));
    screenManager->addScreen(s, "sceneforest");
    
    s = new Scene(player, &window, screenManager, resourcePath() + "desert.txt", "desert.tmx", Vector2f(120, 650), Vector2f(80, 100));
    screenManager->addScreen(s, "scenedesert");
    
    s = new Scene(player, &window, screenManager, resourcePath() + "plage.txt", "plage.tmx", Vector2f(40, 80), Vector2f(48, 48));
    screenManager->addScreen(s, "scenebeach");
    
    s = new Scene(player, &window, screenManager, resourcePath() + "final.txt", "final.tmx", Vector2f(80, 363), Vector2f(100, 100), true);
    screenManager->addScreen(s, "scenefinal");
    
    screenManager->addScreen(new GameOverScreen(screenManager), "gameover");
    screenManager->addScreen(new WinScreen(screenManager), "win");
    screenManager->addScreen(new EndScreen(screenManager), "end");
    screenManager->addScreen(new MenuScreen(screenManager, &window, MenuScreen::BEGIN), "menubegin");
    screenManager->addScreen(new MenuScreen(screenManager, &window, MenuScreen::PAUSE), "menupause");
    screenManager->addScreen(new MenuScreen(screenManager, &window, MenuScreen::WON), "menuwon");
    screenManager->addScreen(new MenuScreen(screenManager, &window, MenuScreen::LOST), "menulost");
    
    screenManager->addScenarioScreen(new ScenarioScreen(&window, screenManager, "Intro_Johnny.png"), "intro1");
    screenManager->addScenarioScreen(new ScenarioScreen(&window, screenManager, "Intro_Daniel.png"), "intro2");
    screenManager->addScenarioScreen(new ScenarioScreen(&window, screenManager, "Intro_texte.png"), "intro3");
    
    screenManager->addScenarioScreen(new ScenarioScreen(&window, screenManager, "afterscene1_text1.png"), "scenario_1.1");
    screenManager->addScenarioScreen(new ScenarioScreen(&window, screenManager, "afterscene1_text2.png"), "scenario_1.2");
    screenManager->addScenarioScreen(new ScenarioScreen(&window, screenManager, "afterscene1_tournament.png"), "scenario_1.3");
    
    screenManager->addScenarioScreen(new ScenarioScreen(&window, screenManager, "afterscene2_text1.png"), "scenario_2.1");
    
    screenManager->addScenarioScreen(new ScenarioScreen(&window, screenManager, "afterscene3_text1.png"), "scenario_3.1");
    screenManager->addScenarioScreen(new ScenarioScreen(&window, screenManager, "afterscene3_text2.png"), "scenario_3.2");
    
    screenManager->addScenarioScreen(new ScenarioScreen(&window, screenManager, "final_text1.png", false, true), "final1");
    
    screenManager->addScenarioScreen(new ScenarioScreen(&window, screenManager, "legbreak1.png", true), "legbreak1");
    screenManager->addScenarioScreen(new ScenarioScreen(&window, screenManager, "legbreak2.png", true), "legbreak2");
    screenManager->addScenarioScreen(new ScenarioScreen(&window, screenManager, "legbreak3.png", true), "legbreak3");
    screenManager->addScenarioScreen(new ScenarioScreen(&window, screenManager, "legbreak4.png", true), "legbreak4");
    
    screenManager->addScenarioScreen(new ScenarioScreen(&window, screenManager, "afterlegbreak_1.png"), "legbreak5");
    
    screenManager->addScenarioScreen(new ScenarioScreen(&window, screenManager, "lastscene_img1.png"), "endscene1");
    screenManager->addScenarioScreen(new ScenarioScreen(&window, screenManager, "lastscene_img2.png", true), "endscene2");
    screenManager->addScenarioScreen(new ScenarioScreen(&window, screenManager, "lastscene_img3.png", true), "endscene3");
    
    screenManager->addScenarioScreen(new ScenarioScreen(&window, screenManager, "lastscene_img4.png", true), "endscene4");
    screenManager->addScenarioScreen(new ScenarioScreen(&window, screenManager, "lastscene_img5.png", true), "endscene5");
    
    screenManager->addScenarioScreen(new ScenarioScreen(&window, screenManager, "final_lasttext.png"), "lasttext");
    
    screenManager->setScreen("menubegin");
    
    oldCurrScreenKey = "scenebeach";
}

Game::~Game()
{
    delete screenManager;
    delete player;
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
                    if (screenManager->getCurrentScreenKey().find("menu") == -1)
                    {
                        oldCurrScreenKey = screenManager->getCurrentScreenKey();
                        screenManager->setScreen("menupause");
                    }
                }
                /*
                if(event.key.code == Keyboard::Num1)
                {
                    if(screenManager->getSceneCount() != 1)
                    {
                        screenManager->setScene(1);
                        screenManager->setSceneCount(1);
                    }
                }
                if(event.key.code == Keyboard::Num2)
                {
                    if(screenManager->getSceneCount() != 2)
                    {
                        screenManager->setScene(2);
                        screenManager->setSceneCount(2);
                    }
                }
                if(event.key.code == Keyboard::Num3)
                {
                    if(screenManager->getSceneCount() != 3)
                    {
                        screenManager->setScene(3);
                        screenManager->setSceneCount(3);
                    }
                }
                if(event.key.code == Keyboard::Num4)
                {
                    if(screenManager->getSceneCount() != 4)
                    {
                        screenManager->setScene(4);
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
                */
            }
          
            screenManager->handleInput(event);
        }
        
        screenManager->update(ellapsed);
        
        window.clear(sf::Color(205, 201, 201));
        screenManager->render(window);
        window.display();
    }
}