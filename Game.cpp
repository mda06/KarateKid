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
            enemies.back()->setColor(Color::Magenta);
            enemies.back()->getFighterCharacteristics().setHealthAndMaxHealth(350);
            enemies.back()->setMaxVel(Vector2f(1, .5f));
            enemies.back()->setAccel(Vector2f(.4f, .9f));
            enemies.back()->getFighterCharacteristics().getAtkFootState().setCooldown(2);
            enemies.back()->getFighterCharacteristics().getAtkPunchState().setCooldown(2);
            enemies.back()->getFighterCharacteristics().getBlockState().setCooldown(2);
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
        if(event.key.code == Keyboard::W)
            player->attackFoot();
        if(event.key.code == Keyboard::X)
            player->attackPunch();
        if(event.key.code == Keyboard::C)
            player->block();
        
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
    for(int i = enemies.size() - 1; i >= 0; i--)
    {
        Entity *e = enemies[i];
        e->update(time);
        if(e->isDeadAnimFinished())
        {
            enemies.erase(enemies.begin() + i);
            delete e;
        }
        if(!e->getFighterCharacteristics().isDead()) {
            float ex = e->getPosition().x, px = player->getPosition().x;
            if(ex > px)
            {
                if(ex - px < e->getFighterCharacteristics().getRangeHit() * 3 + e->getGlobalBounds().width)
                {
                    e->setOrientation(LEFT);
                    e->attackPunch();
                }
            }
            else if(ex < px)
            {
                if(px - ex < e->getFighterCharacteristics().getRangeHit() * 3 + player->getGlobalBounds().width)
                {
                    e->setOrientation(RIGHT);
                    e->attackPunch();
                }
            }
        }
        
    }
    
    player->update(time);
    if (player->isDeadAnimFinished() || player->getGlobalBounds().top > 500)
    {
        player->init();
        initEnemies();
    }
        
    updateView();
}

void Game::updateView()
{
    Vector2f s = mapView.getSize();
    float x = player->getPosition().x;
    if(x < s.x / 2) x = s.x / 2;
    mapView.setCenter(x, mapView.getCenter().y);
    
    std::stringstream stream;
    stream << "Position: " << std::fixed << std::setprecision(0) << player->getPosition().x << "/" << player->getPosition().y << std::endl << "Fight state: " << player->getFighterCharacteristics().getFightState() << std::endl << "Health: " << player->getFighterCharacteristics().getHealth() << "/" << player->getFighterCharacteristics().getMaxHealth();
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
    {
        e->render(window);
        e->drawHpBar(window, true);
    }
    player->render(window);
    window.setView(hudView);
    window.draw(txtPosition);
    player->drawHpBar(window);
    player->drawEnergyBar(window);
    window.display();
}

Entity* Game::getPlayer()
{
    return player;
}

std::vector<Entity*> Game::getEnemies()
{
    return enemies;
}