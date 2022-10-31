//
// Created by hector on 31/10/22.
//

#include "World.h"

World::World() {
    _map = FileReader::readMap(_mapPath);
    _player.xpos = 30;
    _player.ypos = 30;
    _player.angle = M_PI / 2;
}

World::~World() {
}

void World::render() {

}

void World::drawlines() {

}
