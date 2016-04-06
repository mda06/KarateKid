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
    AbstractScreen* tmp = curScreen;
    if(curScreen != nullptr)
        curScreen->leave();
    
    curScreen = screens[key];
    if(curScreen != nullptr)
            curScreen->enter();
    else
        curScreen = tmp;
}

void ScreenManager::setScreen(int i)
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
        setScreen(1);
        passed = true;
    }
    else if (scenarioCount == 6)
    {
        setScreen(2);
    }
    else
    {
        scenarioCount++;
    
        setScenarioScreen(scenarioCount);
    }
}

void ScreenManager::initScenes()
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

std::string ScreenManager::getCurrentScreenKey() const
{
    for(auto it = screens.begin();it != screens.end(); ++it)
        if(it->second == curScreen)
            return it->first;
    
    return "Not found";
}

int ScreenManager::getCurrentScreenNumber() const
{
    std::string key = getCurrentScreenKey();
    
    
    if(key == "scenebeach")
        return 1;
    else if(key == "sceneforest")
        return 2;
    else if(key == "scenedesert")
        return 3;
    else if(key == "scenefinal")
        return 4;
    else
        return -1;
}

AbstractScreen *ScreenManager::getCurrentScreen()
{
    return curScreen;
}

void ScreenManager::nextScene()
{
    sceneCount++;
    initScenes();
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