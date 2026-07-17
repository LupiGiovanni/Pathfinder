//
// Created by gionimbus on 7/13/26.
//

#ifndef LITTLE_PROGRAM_ASTERISM_H
#define LITTLE_PROGRAM_ASTERISM_H

#include <array>
#include "State.h"

struct Asterism {
    Asterism ();
    explicit Asterism (const std::array<Point, 3>& points);
    Asterism (double p0_x, double p1_x, double p2_x, double p0_y, double p1_y, double p2_y);
    bool is_valid () const;
    void print () const;

    std::array<Point, 3> p;
};

inline State convert (const Asterism& asterism) {
    std::array<Discrete_point, 3> arr;
    for (int i = 0; i < 3; i++)
        arr[i] = convert( asterism.p[i] );
    State s (arr);
    return s;
}

inline Asterism convert (const State& state) {
    std::array<Point, 3> arr;
    for (int i = 0; i < 3; i++)
        arr[i] = convert( state.p[i] );
    Asterism a (arr);
    return a;
}


#endif //LITTLE_PROGRAM_ASTERISM_H
