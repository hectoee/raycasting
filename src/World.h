//
// Created by hector on 31/10/22.
//

#ifndef RAYCASTING_WORLD_H
#define RAYCASTING_WORLD_H

#include <vector>
#include <string>
#include "Renderer.h"
#include "FileReader.h"
#include "Color.h"
#include <math.h>

using Map = std::vector<std::vector<int>>;

class World {
private:
    Map _map;
    std::string _mapPath;

    const unsigned int _tileSize = 64; // pixels
    const unsigned int _numberTilesX = 8;
    const unsigned int _numberTilesY = _numberTilesX;

    struct Player {
        int xpos;
        int ypos;
        float angle;
        int sizeInPX;
        float speed;
    };

    Player _player;

public:
    World();
    virtual ~World();

    void render();

    void moveUP();

    void moveDOWN();

    void turnRIGHT();

    void turnLEFT();

private:
    void drawMap() const;

    void drawPlayer() const;

    void drawRays() const;

    float dist(float, float, float, float) const;
};


#endif //RAYCASTING_WORLD_H
