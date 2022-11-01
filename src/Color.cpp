//
// Created by hector on 01/11/22.
//

#include "Color.h"


Color Color::Green = Color(0, 255, 0);
Color Color::Blue  = Color(0, 0, 255);
Color Color::Red   = Color(255, 0, 0);

Color::Color(unsigned int r, unsigned int g, unsigned int b) {
    _c[0] = r;
    _c[1] = g;
    _c[2] = b;
}

Color::~Color() {}

unsigned int  Color::operator[](unsigned int index) const {
    assert(index <= 2 && index >= 0);
    return _c[index];
}