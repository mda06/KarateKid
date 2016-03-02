//
//  Game.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 29/02/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include <iostream>
#include "Game.h"
#include "ResourcePath.hpp"

Game::Game() : window(VideoMode(640, 480), "Karate Kid 1984"), ml(resourcePath())
{
    colHandler = new CollisionHandler();
    player = new Entity(colHandler);
}

Game::~Game()
{
    delete player;
    delete colHandler;
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
    mapView.reset(FloatRect(0, 0, window.getSize().x, window.getSize().y));
    
    player->init();
}

void Game::handleInput()
{
    // Close window: exit
    if (event.type == sf::Event::Closed) {
        window.close();
    }
    
    // Escape pressed: exit
    if (event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Escape) {
            window.close();
        }
        if(event.key.code == Keyboard::Right) player->setDirection(RIGHT);
        if(event.key.code == Keyboard::Left) player->setDirection(LEFT);
        if(event.key.code == Keyboard::Space || event.key.code == Keyboard::Up) player->jump();
    }
    if(event.type == Event::KeyReleased)
    {
        if(event.key.code == Keyboard::Right || event.key.code == Keyboard::Left)
            player->setDirection(STOP);
    }
    
    //mapView.setCenter(Mouse::getPosition().x, Mouse::getPosition().y);
}

void Game::update(float dt)
{
    ml.UpdateQuadTree(FloatRect(mapView.getViewport().left, mapView.getViewport().top, mapView.getViewport().width * window.getSize().x, mapView.getViewport().height * window.getSize().y));
    colHandler->setObjects(ml.QueryQuadTree(player->getGlobalBounds()));
    
    player->update(dt);
}

void Game::printFloatRect(const FloatRect &r)
{
    std::cout << r.left << "/" << r.top << "/" << r.width << "/" << r.height << std::endl;
    
}

void Game::render()
{
    window.clear();
    window.setView(mapView);
    ml.Draw(window, MapLayer::DrawType::All);
    player->render(window);
    window.display();
}