//
// Created by gionimbus on 7/13/26.
//

#ifndef LITTLE_PROGRAM_DISCRETE_POINT_H
#define LITTLE_PROGRAM_DISCRETE_POINT_H


#include "helper.h"

struct Discrete_point {
    Discrete_point ();
    Discrete_point (long x, long y);

    bool operator== (const Discrete_point& other) const;
    bool operator!= (const Discrete_point& other) const;

    long x;
    long y;
};

inline Discrete_point convert (const Point& continuous_point) {
    Discrete_point dp (
        convert( continuous_point.x() ),
        convert( continuous_point.y() )
    );
    return dp;
}

inline Point convert (const Discrete_point& discrete_point) {
    Point cp (
        convert( discrete_point.x ),
        convert( discrete_point.y )
    );
    return cp;
}


#endif //LITTLE_PROGRAM_DISCRETE_POINT_H
