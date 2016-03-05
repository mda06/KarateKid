//
//  Game.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 29/02/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Game.h"
#include "ResourcePath.hpp"

Game::Game() : window(VideoMode(640, 480), "Karate Kid 1984"), ml(resourcePath()), filePath(resourcePath() + "enemies.txt")
{
    colHandler = new CollisionHandler(this);
    player = new Entity(colHandler, Vector2f(60, 430));
}

Game::~Game()
{
    for(Entity* e : enemies)
        delete e;
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
     
        update(ellapsed);
        render();
    }
}

void Game::init()
{
    std::cout << "Loading map... " << ml.Load("testmap.tmx") << std::endl;;
    
    mapView.reset(FloatRect(0, 0, window.getSize().x, window.getSize().y));
    hudView.reset(FloatRect(0, 0, window.getSize().x, window.getSize().y));
    
    player->init();
    initEnemies();
    
    //Change with quadtree for optimisation and don't update enemies not in the range of the rect
    for(MapLayer o : ml.GetLayers())
    {
        if(o.name == "Col")
        {
            colHandler->setObjects(o.objects);
        }
    }
    
    if(!font.loadFromFile(resourcePath() + "master_of_break.ttf"))
        std::cout << "Can't load font !" << std::endl;
    txtPosition.setFont(font);
    txtPosition.setCharacterSize(20);
}

void Game::initEnemies()
{
    for(Entity* e : enemies)
        delete e;
    enemies.clear();
    std::string line;
    std::ifstream file(filePath);
    if (file.is_open())
    {
        while ( getline (file,line) )
        {
            std::string token, delim(",");
            int x, y, i = 0;
            while(token != line){
                token = line.substr(0,line.find_first_of(delim));
                line = line.substr(line.find_first_of(delim) + 1);
                
                if(i == 0) x = std::stoi(token.c_str());
                else y = std::stoi(token.c_str());
                i++;
            }
            enemies.push_back(new Entity(colHandler, Vector2f(x, y)));
            enemies.back()->init();
            std::cout << "Added enemy at " << x << "/" << y << std::endl;
        }
        file.close();
    }
    else
    {
        std::cout << "Can't open enemies file" << std::endl;
    }
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
        
        if(event.key.code == Keyboard::R)
        {
            player->init();
            initEnemies();

        }
    }
    if(event.type == Event::KeyReleased)
    {
        if(event.key.code == Keyboard::Right || event.key.code == Keyboard::Left)
            player->setDirection(STOP);
    }
}

void Game::update(Time time)
{
    for(Entity* e : enemies)
        e->update(time);
    
    player->update(time);
    updateView();
}

void Game::updateView()
{
    Vector2f s = mapView.getSize();
    float x = player->getPosition().x;
    if(x < s.x / 2) x = s.x / 2;
    mapView.setCenter(x, mapView.getCenter().y);
    double pi = 3.14159265359;
    std::stringstream stream;
    stream << "Position: " << std::fixed << std::setprecision(0) << player->getPosition().x << "/" << player->getPosition().y;
    txtPosition.setString(stream.str());
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
    for(Entity* e : enemies)
        e->render(window);
    player->render(window);
    window.setView(hudView);
    window.draw(txtPosition);
    window.display();
}

std::vector<Entity*> Game::getEnemies()
{
    return enemies;
}