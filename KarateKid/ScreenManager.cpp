//
//  ScreenManager.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 15/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "ScreenManager.h"
#include "Scene.h"
#include <iostream>

ScreenManager::ScreenManager() : curScreen(nullptr), sceneCount(1), scenarioCount(0), passed(false)
{}

ScreenManager::~ScreenManager()
{
    for(auto it = screens.begin();it != screens.end(); ++it)
        delete it->second;
}

void ScreenManager::addScreen(AbstractScreen* as, std::string key)
{
    screens[key] = as;
}

void ScreenManager::addScenarioScreen(ScenarioScreen* ss, std::string key)
{
    screens[key] = ss;
    scenarioScreens.push_back(ss);
}

void ScreenManager::handleInput(Event &event)
{
    curScreen->handleInput(event);
}

void ScreenManager::update(Time time)
{
    curScreen->update(time);
}

void ScreenManager::render(RenderTarget &rt)
{
    curScreen->render(rt);
}

void ScreenManager::setScreen(std::string key)
{
    oldScreenKey = getCurrentScreenKey();
    
    AbstractScreen* tmp  = curScreen;
    if(curScreen != nullptr)
        curScreen->leave();
    
    curScreen = screens[key];
    if(curScreen != nullptr)
            curScreen->enter();
    else
        curScreen = tmp;
}

void ScreenManager::setScene(int i)
{
    switch(i)
    {
        case 1:
            setScreen("scenebeach");
            break;
        case 2:
            setScreen("sceneforest");
            break;
        case 3:
            setScreen("scenedesert");
            break;
        case 4:
            setScreen("scenefinal");
            break;
        default:
            setScreen("scenebeach");
            break;
    }
}

void ScreenManager::setScenarioScreen(int i)
{
    scenarioCount = i;
    
    AbstractScreen* tmp = curScreen;
    if(curScreen != nullptr)
        curScreen->leave();
    
    curScreen = scenarioScreens[scenarioCount - 1];
    if(curScreen != nullptr)
        curScreen->enter();
    else
        curScreen = tmp;
}


void ScreenManager::setNextScenarioScreen()
{
    if(scenarioCount == 3 && !passed)
    {
        setScene(1);
        passed = true;
    }
    else if (scenarioCount == 6 && !passed)
    {
        setScene(2);
        passed = true;
    }
    else if (scenarioCount == 7 && passed)
    {
        setScene(3);
        passed = false;
    }
    else if (scenarioCount == 9 && !passed)
    {
        setScene(4);
        passed = true;
    }
    else if (scenarioCount == 10 && passed)
    {
        setScene(4);
        passed = false;
    }
    else if (scenarioCount == 21)
    {
        setScreen("end");
        passed = false;
    }
    else
    {
        scenarioCount++;
        passed = false;
        
        setScenarioScreen(scenarioCount);
    }
}

void ScreenManager::initAllScenes()
{
    for(auto it = screens.begin();it != screens.end(); ++it)
    {
        std::string key = it->first;
        if (key.find("scene") != std::string::npos) {
            std::cout << "Initializating: " << key << '\n';
            Scene* s = (Scene*)it->second;
            s->init();
        }
    }
}

void ScreenManager::initScene(int s)
{
    std::string key;
    switch(s)
    {
        case 1:
            key = "scenebeach";
            break;
        case 2:
            key = "sceneforest";
            break;
        case 3:
            key = "scenedesert";
            break;
        case 4:
            key = "scenefinal";
            break;
        default:
            key = "scenebeach";
            break;
    }
    
    for(auto it = screens.begin();it != screens.end(); ++it)
    {
        if (it->first.find(key) != std::string::npos)
        {
            std::cout << "Initializating: " << key << '\n';
            Scene* s = (Scene*)it->second;
            s->init();
        }
    }
}

std::string ScreenManager::getOldScreenKey()
{
    return oldScreenKey;
}

std::string ScreenManager::getCurrentScreenKey() const
{
    for(auto it = screens.begin();it != screens.end(); ++it)
        if(it->second == curScreen)
            return it->first;
    
    return "Not found";
}

AbstractScreen *ScreenManager::getCurrentScreen()
{
    return curScreen;
}

void ScreenManager::nextScene()
{
    sceneCount++;
    setScreen("win");
}

int ScreenManager::getSceneCount()
{
    return sceneCount;
}

void ScreenManager::setSceneCount(int sc)
{
    sceneCount = sc;
}

int ScreenManager::getTotalScenes()
{
    int count = 0;
    
    for(auto it = screens.begin();it != screens.end(); ++it)
    {
        if(it->first.find("scene") != -1)
            count++;
    }
    
    return count;
}