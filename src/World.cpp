//
// Created by hector on 31/10/22.
//

#include "World.h"

World::World() {
    _mapPath = "../maps/map2.txt";
    _map = FileReader::readMap(_mapPath);
    _player.xpos = 75;
    _player.ypos = 75;
    _player.angle = M_PI_2f;
    _player.sizeInPX = 10;
    _player.speed = 4.0f;
}

World::~World() {
}

void World::render() {
    drawMap();
    drawPlayer();
    drawRays();
}

void World::drawMap() const{
    const Renderer & renderer = Renderer::getInstance();

    for (int i = 0; i < _map.size(); i++) {
        for (int j = 0; j < _map[i].size(); j++) {
            // a wall
            if (_map[j][i] == 1) {
                renderer.drawSquare(i * _tileSize, j * _tileSize, _tileSize, Color::Green);
            }
        }
    }
}

void World::drawPlayer() const {
    const Renderer & renderer = Renderer::getInstance();

    renderer.drawSquare(_player.xpos, _player.ypos, _player.sizeInPX, Color::Blue);
    renderer.drawLine(_player.xpos + _player.sizeInPX/2, _player.ypos+ _player.sizeInPX/2, 20 * cos(_player.angle) + _player.xpos+ _player.sizeInPX/2, 20 * sin(_player.angle) + _player.ypos+ _player.sizeInPX/2, Color::Blue);
}

void World::moveUP() {
    // check first for collision
    float offx = 5 * cos(_player.angle) + (float) _player.xpos;
    float offy = 5 * sin(_player.angle) + (float) _player.ypos;
    if (_map[offy / 64][offx / 64])
        return;

    float vx = cos(_player.angle);
    float vy = sin(_player.angle);
    if (sqrt(vx * vx + vy * vy) != 0) {
        vx /= sqrt(vx * vx + vy * vy);
        vy /= sqrt(vx * vx + vy * vy);
    }

    float newx = _player.speed * vx + (float) _player.xpos;
    float newy = _player.speed * vy + (float) _player.ypos;

    _player.xpos = (int) newx;
    _player.ypos = (int) newy;
}

void World::moveDOWN() {
    // check first for collision
    float offx = - 5 * cos(_player.angle) + (float) _player.xpos;
    float offy = - 5 * sin(_player.angle) + (float) _player.ypos;
    if (_map[offy / 64][offx / 64])
        return;

    float vx = - cos(_player.angle);
    float vy = - sin(_player.angle);
    if (sqrt(vx * vx + vy * vy) != 0) {
        vx /= sqrt(vx * vx + vy * vy);
        vy /= sqrt(vx * vx + vy * vy);
    }

    float newx = _player.speed * vx + (float) _player.xpos;
    float newy = _player.speed * vy + (float) _player.ypos;

    _player.xpos = (int) newx;
    _player.ypos = (int) newy;
}

void World::turnLEFT() {
    _player.angle -= 0.1;
    if (_player.angle < 0)
        _player.angle += 2 * M_PI;
}

void World::turnRIGHT() {
    _player.angle += 0.1;
    if (_player.angle > 2 * M_PI)
        _player.angle -= 2 * M_PI;
}

float World::dist(float x1, float y1, float x2, float y2) const {
    return sqrt( (y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1) );
}

void World::drawRays() const{
    int r, mx, my, dof, disT;
    float rx, ry, ra, xo, yo;
    const int nbOfRays = 250;
    const Renderer & renderer = Renderer::getInstance();

    ra = _player.angle - M_PI / 6;
    if (ra < 0) ra += 2 * M_PI;
    if (ra > 2 * M_PI) ra -= 2 * M_PI;

    for (r = 0; r < nbOfRays; r++) {
        /** Check horizontal lines **/
        dof = 0;
        float disH = 1000000;
        float hx = _player.xpos;
        float hy = _player.ypos;
        float aTan = -1 / tan(ra);
        // looking up
        if (ra > M_PI) {
            ry = (((int)_player.ypos >> 6) << 6) - 0.0001;
            rx = (_player.ypos - ry) * aTan + _player.xpos;
            yo = -64;
            xo = -yo * aTan;
        }
        // looking down
        if (ra < M_PI) {
            ry = (((int)_player.ypos >> 6) << 6) + 64;
            rx = (_player.ypos - ry) * aTan + _player.xpos;
            yo = 64;
            xo = -yo * aTan;
        }
        // looking straight horizontally
        if (ra == 0 || ra == M_PI) {
            rx = _player.xpos;
            ry = _player.ypos;
            dof = 8;
        }
        while (dof < 8) {
            mx = (int) (ry) >> 6;
            my = (int) (rx) >> 6;
            // we hit wall
            if (mx < _numberTilesX && my < _numberTilesY && _map[mx][my] == 1) {
                hx = rx;
                hy = ry;
                disH = dist(_player.xpos, _player.ypos, hx, hy);
                dof = 8;
            }
            // next line
            else {
                rx += xo;
                ry += yo;
                dof ++;
            }
        }

        /** Check vertical lines **/
        dof = 0;
        float disV = 1000000;
        float vx = _player.xpos;
        float vy = _player.ypos;
        float nTan = -tan(ra);
        // looking left
        if (ra > M_PI_2f && ra < 3 * M_PI_2f) {
            rx = (((int)_player.xpos >> 6) << 6) - 0.0001;
            ry = (_player.xpos - rx) * nTan + _player.ypos;
            xo = -64;
            yo = -xo * nTan;
        }
        // looking right
        if (ra < M_PI_2f || ra > 3 * M_PI_2f) {
            rx = (((int)_player.xpos >> 6) << 6) + 64;
            ry = (_player.xpos - rx) * nTan + _player.ypos;
            xo = 64;
            yo = -xo * nTan;
        }
        // looking straight vertically
        if (ra ==  M_PI_2f|| ra == 3 * M_PI_2f) {
            rx = _player.xpos;
            ry = _player.ypos;
            dof = 8;
        }
        while (dof < 8) {
            mx = (int) (ry) >> 6;
            my = (int) (rx) >> 6;
            // we hit wall
            if (mx < _numberTilesX && my < _numberTilesY && _map[mx][my] == 1) {
                vx = rx;
                vy = ry;
                disV = dist(_player.xpos, _player.ypos, vx, vy);
                dof = 8;
            }
            // next line
            else {
                rx += xo;
                ry += yo;
                dof ++;
            }
        }

        Color c;
        if (disH < disV){
            rx = hx;
            ry = hy;
            disT = disH;
            c = Color::DarkGreen;
        }
        if (disV < disH){
            rx = vx;
            ry = vy;
            disT = disV;
            c = Color::Green;
        }

        Renderer::getInstance().drawLine(_player.xpos, _player.ypos, rx, ry, Color::Red);


        /** Draw 3D Scene **/
        int screenHeight = 160;
        int screenWidth = 400;



        float ca = _player.angle - ra;
        if (ca < 0) ca += 2 * M_PI;
        if (ca > 2 * M_PI) ca -= 2 * M_PI;
        disT = (float) disT * cos(ca);
        float lineH = ( (float) (_tileSize * screenWidth)) / (float) disT;
        //if (lineH > screenHeight) lineH = screenHeight;
        float lineOffset =  screenHeight - lineH / 2.0;

        renderer.drawLine(r*3+530, lineOffset+195, r*3+530, lineH+lineOffset+195, c);


        ra += M_PI / 3 / nbOfRays;
        if (ra < 0) ra += 2 * M_PI;
        if (ra > 2 * M_PI) ra -= 2 * M_PI;
    }
}


