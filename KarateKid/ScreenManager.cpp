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

ScreenManager::ScreenManager() : curScreen(nullptr), sceneCount(1)
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

void ScreenManager::handleInput(Event &event)
{
    curScreen->handleInput(event);
}

void ScreenManager::update(Time time)
{
    /*
    if(getCurrentScreenKey() == "sceneforest")
        sceneCount = 1;
    else if(getCurrentScreenKey() == "scenedesert")
        sceneCount = 2;
    */
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