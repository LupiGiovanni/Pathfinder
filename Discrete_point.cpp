//
// Created by gionimbus on 7/13/26.
//

#include "Discrete_point.h"

Discrete_point::Discrete_point (): x(0), y(0) {}

Discrete_point::Discrete_point (long x, long y): x(x), y(y) {}

bool Discrete_point::operator== (const Discrete_point& other) const {
    return this->x == other.x && this->y == other.y;
}

bool Discrete_point::operator!= (const Discrete_point& other) const {
    return this->x != other.x || this->y != other.y;
}