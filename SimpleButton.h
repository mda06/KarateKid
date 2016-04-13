//
//  SimpleButton.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 14/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__SimpleButton__
#define __KarateKid__SimpleButton__

#include <SFML/Graphics.hpp>
using namespace sf;

class SimpleButton
{
private:
    Texture textBg;
    Sprite sprBg;
    Text text;
    Font font;
    bool isClicked;
    
public:
    SimpleButton(Vector2f pos, std::string path, std::string txt);
    void handleInput(Event &event, Vector2f mousePos);
    void handleInput(Event &event, bool focus);
    void render(RenderTarget &rt);
    bool clicked();
    void setScale(float x, float y);
    Sprite getSprite();
    void setText(std::string txt);
    std::string getText();
    
};


#endif /* defined(__KarateKid__SimpleButton__) */
