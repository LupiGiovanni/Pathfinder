//
// Created by gionimbus on 7/13/26.
//

#include "Asterism.h"
#include "Board_set.h"

Asterism::Asterism (): p { Point(0., 0.), Point(0., 0.), Point(0., 0.) } {}

Asterism::Asterism (const std::array<Point, 3>& points): p (points) {}

Asterism::Asterism(double p0_x, double p1_x, double p2_x, double p0_y, double p1_y, double p2_y):
    p { Point(p0_x, p0_y), Point(p1_x, p1_y), Point(p2_x, p2_y) } {}

bool Asterism::is_valid () const {
    Asterism a = *this;
    Board_set temporary;
    temporary.teleport_home();
    if ( temporary.align(a) )
        return true;
    return false;
}

void Asterism::print () const {
    std::cout << "("
              << p[0].x() << ", " << p[0].y() << "), ("
              << p[1].x() << ", " << p[1].y() << "), ("
              << p[2].x() << ", " << p[2].y() << ")"
              << std::endl;
}