//
// Created by hector on 31/10/22.
//

#ifndef RAYCASTING_WORLD_H
#define RAYCASTING_WORLD_H

#include <vector>
#include <string>
#include "Renderer.h"
#include "FileReader.h"
#include <math.h>

using Map = std::vector<std::vector<int>>;

class World {
private:
    Map _map;
    const std::string _mapPath = "../maps/map1.txt";

    const unsigned int _tileSize = 20; // pixels

    struct Player {
        int xpos;
        int ypos;
        double angle;
    };

    Player _player;

public:
    World();
    virtual ~World();

    void render();

    void moveUP() { _player.ypos ++; }

    void moveDOWN() { _player.ypos --; }

    void moveRIGHT() { _player.xpos ++; }

    void moveLEFT() { _player.xpos --; }

private:
    void drawlines();
};


#endif //RAYCASTING_WORLD_H
