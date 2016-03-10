//
//  SoundManager.cpp
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 10/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#include "SoundManager.h"
#include "ResourcePath.hpp"
#include <iostream>

SoundManager::SoundManager()
{
    if (!bufPunch.loadFromFile(resourcePath() + "punch.wav"))
    {
        std::cout << "Can't load punch sound" << std::endl;
        return;
    }
    
    soundPunch.setBuffer(bufPunch);
}

void SoundManager::playPunch()
{
    soundPunch.play();
}
