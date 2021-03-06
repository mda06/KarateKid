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
#include "ScreenManager.h"

Scene::Scene(Player *p, RenderWindow *window, ScreenManager *sm, std::string enemiesFile, std::string mapName, Vector2f pos, Vector2f entitySize, bool fixed) : window(window), AbstractScreen(sm), ml(resourcePath()), enemiesFile(enemiesFile), keyBlock(Keyboard::C), mapName(mapName), entitySize(entitySize), fixed(fixed), timerDone(false), playerPos(pos), readyToBreakLeg(false)
{
    colHandler = new CollisionHandler(this);
    
    player = p;
    
    if(!font.loadFromFile(resourcePath() + "master_of_break.ttf"))
        std::cout << "Can't load font !" << std::endl;
    txtPosition.setFont(font);
    txtPosition.setCharacterSize(20);
    
    srand(time(NULL));
    
    view = FloatRect(0, 0, 640, 480);
    mapView.reset(view);
    hudView.reset(FloatRect(0, 0, 640, 480));
    
    if(mapName.find("desert") != -1)
        mapView.zoom(1.7);
    
    std::cout << "Loading map " << mapName << "... " << ml.Load(mapName) << std::endl;;
    //Change with quadtree for optimisation and don't update enemies not in the range of the rect
    for(MapLayer o : ml.GetLayers())
    {
        if(o.name == "Col")
        {
            colHandler->setObjects(o.objects);
        }
    }
    
    if(mapName.find("plage") != -1)
        addStoryText("Daniel wants to fight !", Vector2f(4300, 283));
    
    if(mapName.find("final") != -1 && readyToBreakLeg)
        addStoryText("Press W !", Vector2f(320, 150));
}

Scene::~Scene()
{
    for(Entity* e : enemies)
        delete e;
    
    delete colHandler;
    
    for(GameObject* go : gameObjects)
        delete go;
    
    for(Text* t : textInfo)
        delete t;
    
    for(Text* t : storyText)
        delete t;
}

void Scene::init()
{
    player->initToScene(colHandler, entitySize, playerPos);
    initEnemies();
    
    for(GameObject* go : gameObjects)
        delete go;
    gameObjects.clear();
    
    for(Text* t : textInfo)
        delete t;
    textInfo.clear();
    
    for(Text* t : storyText)
        delete t;
    storyText.clear();
    
    if(mapName.find("plage") != -1)
        addStoryText("Daniel wants to fight !", Vector2f(4300, 270));
    if(mapName.find("final") != -1 && readyToBreakLeg)
        addStoryText("Press W !", Vector2f(320, 150));
    
    timerDone = false;
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
            enemies.push_back(new Enemy(colHandler, Vector2f(x, y), health, maxStrength, 1.5f, 1.5f, 1.5f, entitySize));
            enemies.back()->init();
            //enemies.back()->setColor(Color::Magenta);
            std::cout << "Added enemy at " << x << "/" << y << std::endl;
        }
        file.close();
        if(mapName.find("final") != -1)
            enemies.back()->setTargetRange(window->getSize().x);
        else
            enemies.back()->setTargetRange(window->getSize().x / 4);
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
        {
            if(readyToBreakLeg)
            {
                screenManager->setScenarioScreen(11);
            }
            else
                player->attackFoot();
        }
        if(event.key.code == Keyboard::X)
        {
            if(mapName.find("final") != -1)
            {
                if(!readyToBreakLeg)
                {
                    if(enemies[0]->getFighterCharacteristics().willKill(player->getFighterCharacteristics().getDamages()))
                    {
                        readyToBreakLeg = true;
                        screenManager->setScenarioScreen(10);
                    }
                }
            }
            
            if(!readyToBreakLeg)
                player->attackPunch();
        }
        if(event.key.code == keyBlock)
            player->block();
        
        if(event.key.code == Keyboard::R)
        {
            init();
            player->initStats();
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
        if(!fixed)
        {
            float aspectRatio = (float) event.size.height / (float) mapView.getSize().y;
            view = FloatRect(0, 0, event.size.width / aspectRatio, mapView.getSize().y);
            mapView.setSize(event.size.width / aspectRatio, mapView.getSize().y);
        }
    }
}

void Scene::addGameObject(Vector2f pos, bool boss)
{
    if(boss)
    {
        gameObjects.push_back(new GameObjectKey(screenManager, pos));
        return;
    }
    
    int r = rand() % 100;
    if(r < 25) gameObjects.push_back(new GameObjectPotion(pos));
    else if(r < 50) gameObjects.push_back(new GameObjectStrength(pos));
    else if(r < 75) gameObjects.push_back(new GameObjectEnergy(pos));
}

void Scene::update(Time time)
{
    if(mapName.find("final") != -1 && readyToBreakLeg)
    {
        if(storyText.size() < 1)
            addStoryText("Press W !", Vector2f(320, 200));
    }
    
    
    for(int i = enemies.size() - 1; i >= 0; i--)
    {
        Enemy *e = enemies[i];
        e->update(time);
        
        if(e->isDeadAnimFinished())
        {
            addGameObject(e->getPosition(), i == enemies.size() - 1);
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
    if(player->isDeadAnimFinished())
    {
        timerDone = false;
        player->initStats();
        screenManager->setScreen("gameover");
    }
    
    if (player->getGlobalBounds().top > ml.GetMapSize().y)
    {
        player->setDeadAnimFinished(true);
    }
    
    for(int i = gameObjects.size() - 1; i >=0 ; i--)
    {
        GameObject *go = gameObjects[i];
        go->update(time.asSeconds());
        if(go->isUsed())
        {
            addText(go->getString(), go->getPos());
            gameObjects.erase(gameObjects.begin() + i);
        }
    }

    for (int i = 0; i < textInfo.size(); i++)
    {
        Text* t = textInfo[i];
        t->move(0, -30 * time.asSeconds());
        if(t->getPosition().y < 0)
            textInfo.erase(textInfo.begin() + i);
    }
    
    updateView();
}

void Scene::updateView()
{
    Vector2f s = mapView.getSize();
    float x = player->getPosition().x;
    if(x < s.x / 2) x = s.x / 2;
    if(x > ml.GetMapSize().x - s.x / 2) x = ml.GetMapSize().x - s.x / 2;
    float y = player->getPosition().y;
    if(y < s.y / 2) y = s.y / 2;
    if(y > ml.GetMapSize().y - s.y / 2) y = ml.GetMapSize().y - s.y / 2;
    mapView.setCenter(x, y);
    
    std::stringstream stream;
    stream << "Position: " << std::fixed << std::setprecision(0) << player->getPosition().x << "/" << player->getPosition().y << std::endl << "Fight state: " << player->getFighterCharacteristics().getFightState();
    txtPosition.setString(stream.str());
}

void Scene::printFloatRect(const FloatRect &r)
{
    std::cout << r.left << "/" << r.top << "/" << r.width << "/" << r.height;// << std::endl;
}

void Scene::render(RenderTarget &window)
{
    window.setView(mapView);
    ml.Draw(window, MapLayer::DrawType::All);
    for(Text* t : storyText)
        window.draw(*t);
    for(Entity* e : enemies)
    {
        e->render(window);
        e->drawHpBar(window);
    }
    player->render(window);
    for(GameObject* go : gameObjects)
        go->draw(window);
    for(Text* t : textInfo)
        window.draw(*t);
    window.setView(hudView);
    window.draw(txtPosition);
    player->drawHpBar(window);
    player->drawEnergyBar(window);
    player->drawStrengthBar(window);
}

Player* Scene::getPlayer()
{
    return player;
}

std::vector<GameObject*> Scene::getGameObjects()
{
    return gameObjects;
}

std::vector<Enemy*> Scene::getEnemies()
{
    return enemies;
}

void Scene::addText(String txt, Vector2f pos)
{
    textInfo.push_back(new Text(txt, font, 15));
    textInfo[textInfo.size() - 1]->setPosition(pos);
}

void Scene::addStoryText(String txt, Vector2f pos)
{
    storyText.push_back(new Text(txt, font, 20));
    storyText[storyText.size() - 1]->setPosition(pos);
}

void Scene::enter()
{
    if(screenManager->getOldScreenKey() != "menupause" && screenManager->getOldScreenKey() != "final1")
    {
        std::cout << "Initializing " << screenManager->getCurrentScreenKey() << std::endl;
        init();
        
        if(screenManager->getSceneCount() == 1)
            player->initStats();
    }
    
    if(screenManager->getOldScreenKey() == "menulost")
    {
        player->setDirection(RIGHT);
        player->setDirection(STOP);
    }
    
    if(!fixed)
    {
        float aspectRatio = (float) window->getSize().y / (float) mapView.getSize().y;
        view = FloatRect(0, 0, window->getSize().x / aspectRatio, mapView.getSize().y);
        mapView.setSize(window->getSize().x / aspectRatio, mapView.getSize().y);
    }
    else if (!timerDone)
    {
        timer();
    }
}

void Scene::timer()
{
    bool stop = false;
    Clock clock;

    txtTimer.setString("3");
    txtTimer.setFont(font);
    txtTimer.setPosition(320 - txtTimer.getGlobalBounds().width / 2, 240 - txtTimer.getGlobalBounds().height/2);
    txtTimer.setCharacterSize(100);
    
    window->clear();
    render(*window);
    window->draw(txtTimer);
    window->display();
    
    clock.restart();
    while(!stop)
    {
        Time ellapsed = clock.getElapsedTime();
        
        if(ellapsed.asSeconds() >= 4)
            stop = true;
        else if(ellapsed.asSeconds() >= 3)
            txtTimer.setString("Fight");
        else if(ellapsed.asSeconds() >= 2)
            txtTimer.setString("1");
        else if(ellapsed.asSeconds() >= 1)
            txtTimer.setString("2");
        
        txtTimer.setPosition(320 - txtTimer.getGlobalBounds().width / 2, 240 - txtTimer.getGlobalBounds().height/2);
        
        window->clear();
        render(*window);
        window->draw(txtTimer);
        window->display();
    }
    
    timerDone = true;
}