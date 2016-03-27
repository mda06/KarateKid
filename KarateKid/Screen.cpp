//
//  Screen.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 15/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "Screen.h"


AbstractScreen::AbstractScreen(ScreenManager *sm) : screenManager(sm)
{}

AbstractScreen::~AbstractScreen()
{}

void AbstractScreen::enter()
{}

void AbstractScreen::enter(std::string osk)
{}

void AbstractScreen::leave()
{}

ScreenManager* AbstractScreen::getScreenManager()
{
    return screenManager;
}