//
//  GUIBar.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 7/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__GUIBar__
#define __KarateKid__GUIBar__

#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;

class GUIBar
{
private:
    Texture textBack;
    Sprite spriteBack;
    Texture textFront;
    Sprite spriteFront;
    IntRect irFront;
    bool withBack;
    int maxWidth;
    
public:
    GUIBar(std::string pathBack, std::string pathFront, Vector2f pos, int mw, bool withBack = true);
    void draw(RenderTarget &rt);
    void setWithBack(bool b);
    void setPosition(Vector2f pos);
    void setPerc(float perc);
    Vector2f getPos();
    int getWidth();
};

#endif /* defined(__KarateKid__GUIBar__) */
