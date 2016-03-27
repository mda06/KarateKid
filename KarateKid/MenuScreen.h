//
//  MenuScreen.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 14/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__MenuScreen__
#define __KarateKid__MenuScreen__

#include "SimpleButton.h"
#include "Screen.h"

class MenuScreen : public AbstractScreen
{
public:
    enum MenuState {BEGIN, PAUSE, WON, LOST};
private:
    Window *window;
    SimpleButton btnPlay, btnHowTo, btnExit, btnReturn;
    Texture textHowToPlay, textBG;
    Sprite sprHowToPlay, sprBG;
    bool renderHowToPlay, focus;
    int index;
    const int firstIndex, lastIndex;
    Text text;
    Font font;
    MenuState state;
    std::string oldScreenKey;
    
public:
    MenuScreen(ScreenManager* sm, Window* w, MenuState state);
    void handleInput(Event &event);
    void update(Time time);
    void render(RenderTarget &rt);
    void enter(std::string osk);
    void init();
    
};

/*
class MenuScreenBegin : public MenuScreen
{
private:
    SimpleButton btnPlay;
    
public:
    MenuScreenBegin(ScreenManager* sm, Window* w);
};

class MenuScreenPause : public MenuScreen
{
private:
    SimpleButton btnContinue;
    
public:
    MenuScreenPause(ScreenManager* sm, Window* w);
};

class MenuScreenWon : public MenuScreen
{
private:
    SimpleButton btnNext;
    
public:
    MenuScreenWon(ScreenManager* sm, Window* w);
};

class MenuScreenLost : public MenuScreen
{
public:
    MenuScreenLost(ScreenManager* sm, Window* w);
};
*/

#endif /* defined(__KarateKid__MenuScreen__) */
