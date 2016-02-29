//
//  Game.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 29/02/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__Game__
#define __KarateKid__Game__

class Game
{
private:
    void init();
    void handleInput();
    void update(float dt);
    void render();
    
public:
    Game();
    void run();
    
};

#endif /* defined(__KarateKid__Game__) */
