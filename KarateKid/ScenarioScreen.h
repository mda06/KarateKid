//
//  ScenarioScreen.h
//  KarateKid
//
//  Created by Timothy Van Peteghem on 6/04/16.
//  Copyright © 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef ScenarioScreen_h
#define ScenarioScreen_h

#include "Screen.h"

class ScenarioScreen : public AbstractScreen
{
private:
    Texture txt;
    Sprite spr;
    Font font;
    Text text;
    bool video;
    Clock c;
    Time t;
    
public:
    ScenarioScreen(RenderWindow *w, ScreenManager* sm, std::string img, bool video = false);
    void handleInput(Event &event);
    void update(Time time);
    void render(RenderTarget &rt);
    void enter();
    
};

#endif /* ScenarioScreen_h */
