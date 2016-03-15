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

class ScreenManager
{
private:
    std::map<std::string, AbstractScreen*> screens;
    AbstractScreen *curScreen;
public:
    ScreenManager();
    ~ScreenManager();
    void addScreen(AbstractScreen* as, std::string key);
    void handleInput(Event &event);
    void update(Time time);
    void render(RenderTarget &rt);
    void setScreen(std::string key);
    AbstractScreen *getCurrentScreen();
    std::string getCurrentScreenKey() const;
};

#endif /* defined(__KarateKid__ScreenManager__) */
