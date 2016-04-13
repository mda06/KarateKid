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
    RenderWindow *window;
    SimpleButton btnPlay, btnHowTo, btnExit, btnReturn, btnNext;
    Texture txtrInstructions, txtrControls, textBG;
    Sprite sprInstructions, sprControls, sprBG;
    bool renderHowToPlay, renderControls;
    int index;
    const int firstIndex, lastIndex;
    Text textMenu, textControls, textInstructions;
    Font font;
    MenuState state;
    std::string oldScreenKey;
    
public:
    MenuScreen(ScreenManager* sm, RenderWindow* w, MenuState state);
    void handleInput(Event &event);
    void update(Time time);
    void render(RenderTarget &rt);
    void enter();
    void init();
    void changeBtnNextText();
    
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
