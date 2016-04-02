//
//  Scene.h
//  KarateKid
//
//  Created by Michaël Van Meerbeek on 8/03/16.
//  Copyright (c) 2016 Michaël Van Meerbeek. All rights reserved.
//

#ifndef __KarateKid__Scene__
#define __KarateKid__Scene__

#include <tmx/MapLoader.h>
#include <string>
#include <vector>
#include "CollisionHandler.h"
#include "Enemy.h"
#include "Player.h"
#include "GameObject.h"
#include "Screen.h"

using namespace tmx;

class Scene : public AbstractScreen
{
private:
    void initEnemies();
    void updateView();
    void printFloatRect(const FloatRect &r);
    MapLoader ml;
    View mapView, hudView;
    Player *player;
    CollisionHandler *colHandler;
    std::string enemiesFile, mapName;
    std::vector<Enemy*> enemies;
    Font font;
    Text txtPosition, txtTimer;
    Keyboard::Key keyBlock;
    std::vector<GameObject*> gameObjects;
    void addGameObject(Vector2f pos, bool boss);
    std::vector<Text*> textInfo;
    Vector2f entitySize;
    FloatRect view;
    RenderWindow *window;
    bool fixed;

public:
    Scene(RenderWindow *window, ScreenManager *sm, std::string enemiesFile, std::string mapName, Vector2f pos, Vector2f entitySize, bool fixed = false);
    virtual ~Scene();
    void init();
    void handleInput(Event &event);
    void update(Time time);
    void render(RenderTarget &rt);
    std::vector<Enemy*> getEnemies();
    Player* getPlayer();
    std::vector<GameObject*> getGameObjects();
    void addText(String txt, Vector2f pos);
    void enter();
    void timer();
    
};

#endif /* defined(__KarateKid__Scene__) */
