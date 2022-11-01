//
// Created by hector on 01/11/22.
//

#ifndef RAYCASTING_COLOR_H
#define RAYCASTING_COLOR_H

#include <assert.h>


class Color {
private:
    unsigned int _c[3];

public:
    Color(unsigned int = 255, unsigned int = 255, unsigned int = 255);
    virtual ~Color();

    static Color Green;
    static Color Blue;
    static Color Red;

    unsigned int operator[](unsigned int) const;
};


#endif //RAYCASTING_COLOR_H
