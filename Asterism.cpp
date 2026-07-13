//
// Created by gionimbus on 7/13/26.
//

#include "Asterism.h"

Asterism::Asterism (): p { Point(0., 0.), Point(0., 0.), Point(0., 0.) } {}

Asterism::Asterism (const std::array<Point, 3>& points): p (points) {}

Asterism::Asterism(double p0_x, double p1_x, double p2_x, double p0_y, double p1_y, double p2_y):
    p { Point(p0_x, p0_y), Point(p1_x, p1_y), Point(p2_x, p2_y) } {}