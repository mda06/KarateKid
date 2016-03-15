//
//  ScreenManager.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 15/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "ScreenManager.h"

ScreenManager::ScreenManager() : curScreen(nullptr)
{}

ScreenManager::~ScreenManager()
{
    for(auto it = screens.begin();it != screens.end(); ++it)
        delete it->second;
}

void ScreenManager::addScreen(AbstractScreen* as, std::string key)
{
    screens[key] = as;
    setScreen(key);
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
    if(curScreen != nullptr)
        curScreen->leave();
    
    curScreen = screens[key];
    curScreen->enter();
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
