//
//  ScreenManager.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 15/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__ScreenManager__
#define __KarateKid__ScreenManager__

#include "Screen.h"
#include <vector>
#include <string.h>
#include <map>
#include "ScenarioScreen.h"

class ScreenManager
{
private:
    std::map<std::string, AbstractScreen*> screens;
    AbstractScreen *curScreen;
    int sceneCount;
    std::vector<ScenarioScreen*> scenarioScreens;
    int scenarioCount;
    bool passed;
    
public:
    ScreenManager();
    ~ScreenManager();
    void addScreen(AbstractScreen* as, std::string key);
    void addScenarioScreen(ScenarioScreen* ss, std::string key);
    void handleInput(Event &event);
    void update(Time time);
    void render(RenderTarget &rt);
    void setScreen(std::string key);
    void setScreen(int i);
    void setScenarioScreen(int i);
    void setNextScenarioScreen();
    void initScenes();
    AbstractScreen *getCurrentScreen();
    std::string getCurrentScreenKey() const;
    int getCurrentScreenNumber() const;
    void nextScene();
    int getSceneCount();
    void setSceneCount(int sc);
    int getTotalScenes();
    
};

#endif /* defined(__KarateKid__ScreenManager__) */
