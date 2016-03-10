//
//  SoundManager.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 10/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__SoundManager__
#define __KarateKid__SoundManager__

#include <SFML/Audio.hpp>

class SoundManager
{
private:
    sf::SoundBuffer bufPunch;
    sf::Sound soundPunch;
    
public:
    SoundManager();
    void playPunch();
};

#endif /* defined(__KarateKid__SoundManager__) */
