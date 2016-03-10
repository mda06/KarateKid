//
//  Scene.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 8/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "Scene.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "ResourcePath.hpp"

Scene::Scene(std::string enemiesFile, std::string mapName, Vector2f pos) : ml(resourcePath()), enemiesFile(enemiesFile), keyBlock(Keyboard::C), mapName(mapName)
{
    colHandler = new CollisionHandler(this);
    player = new Player(colHandler, pos);
    
    if(!font.loadFromFile(resourcePath() + "master_of_break.ttf"))
        std::cout << "Can't load font !" << std::endl;
    txtPosition.setFont(font);
    txtPosition.setCharacterSize(20);
    
    if(!txtGameOver.loadFromFile(resourcePath() + "gameOver.jpg"))
        std::cout << "Can't load game over texture" << std::endl;
    sprGameOver.setTexture(txtGameOver);
}

Scene::~Scene()
{
    for(Entity* e : enemies)
        delete e;
    delete player;
    delete colHandler;
}

void Scene::init()
{
    std::cout << "Loading map... " << ml.Load(mapName) << std::endl;;
    
    mapView.reset(FloatRect(0, 0, 640, 480));
    hudView.reset(FloatRect(0, 0, 640, 480));
    
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
}

void Scene::initEnemies()
{
    for(Entity* e : enemies)
        delete e;
    enemies.clear();
    std::string line;
    std::ifstream file(enemiesFile);
    if (file.is_open())
    {
        while ( getline (file,line) )
        {
            std::string token, delim(",");
            int x, y, i = 0;
            int health = 450, maxStrength = 80;
            while(token != line){
                token = line.substr(0,line.find_first_of(delim));
                line = line.substr(line.find_first_of(delim) + 1);
                
                if(i == 0) x = std::stoi(token.c_str());
                else if(i == 1) y = std::stoi(token.c_str());
                else if(i == 2) health = std::stoi(token.c_str());
                else if(i == 3) maxStrength = std::stoi(token.c_str());
                i++;
            }
            enemies.push_back(new Enemy(colHandler, Vector2f(x, y), health, maxStrength, 1.5f, 1.5f, 1.5f));
            enemies.back()->init();
            enemies.back()->setColor(Color::Magenta);
            std::cout << "Added enemy at " << x << "/" << y << std::endl;
        }
        file.close();
    }
    else
    {
        std::cout << "Can't open enemies file" << std::endl;
    }
}

void Scene::handleInput(Event &event)
{
    // Escape pressed: exit
    if (event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == Keyboard::Right) player->setDirection(RIGHT);
        if(event.key.code == Keyboard::Left) player->setDirection(LEFT);
        if(event.key.code == Keyboard::Space || event.key.code == Keyboard::Up) player->jump();
        if(event.key.code == Keyboard::W)
            player->attackFoot();
        if(event.key.code == Keyboard::X)
            player->attackPunch();
        if(event.key.code == keyBlock)
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
        
        if(event.key.code == keyBlock)
            player->setDirection(STOP);
    }
    
    if(event.type == Event::Resized)
    {
        /*std::cout << mapView.getSize().x << ", " << mapView.getSize().y << std::endl;
        
        std::cout << "\tRatio: " << aspectRatio << std::endl;*/
        //mapView.setSize(event.size.width * aspectRatio * 1.3f, event.size.height * aspectRatio);
        //float aspectRatio = (float) event.size.width / (float) event.size.height;
        float y = event.size.height;
        mapView.setSize(event.size.width, y);
    }
}

void Scene::update(Time time)
{
    for(int i = enemies.size() - 1; i >= 0; i--)
    {
        Enemy *e = enemies[i];
        e->update(time);
        
        if(e->isDeadAnimFinished())
        {
            enemies.erase(enemies.begin() + i);
            delete e;
        }
        
        if (e->getGlobalBounds().top > 500)
        {
            e->setDeadAnimFinished(true);
        }
        
        if(!e->getFighterCharacteristics().isDead()) {
            e->updateTarget(player);
        }
        
    }
    
    player->update(time);
    
    if (player->getGlobalBounds().top > 500)
    {
        player->setDeadAnimFinished(true);
    }
    
    updateView();
}

void Scene::updateView()
{
    Vector2f s = mapView.getSize();
    float x = player->getPosition().x;
    if(x < s.x / 2) x = s.x / 2;
    if(x > ml.GetMapSize().x - s.x / 2) x = ml.GetMapSize().x - s.x / 2;
    mapView.setCenter(x, mapView.getCenter().y);
    
    std::stringstream stream;
    stream << "Position: " << std::fixed << std::setprecision(0) << player->getPosition().x << "/" << player->getPosition().y << std::endl << "Fight state: " << player->getFighterCharacteristics().getFightState();
    txtPosition.setString(stream.str());
}

void Scene::printFloatRect(const FloatRect &r)
{
    std::cout << r.left << "/" << r.top << "/" << r.width << "/" << r.height << std::endl;
}

void Scene::render(RenderTarget &window)
{
    window.setView(mapView);
    ml.Draw(window, MapLayer::DrawType::All);
    for(Entity* e : enemies)
    {
        e->render(window);
        e->drawHpBar(window);
    }
    player->render(window);
    window.setView(hudView);
    window.draw(txtPosition);
    player->drawHpBar(window);
    player->drawEnergyBar(window);
    player->drawStrengthBar(window);
    if(player->isDeadAnimFinished())
        window.draw(sprGameOver);
}

Player* Scene::getPlayer()
{
    return player;
}

std::vector<Enemy*> Scene::getEnemies()
{
    return enemies;
}