//
// Created by gionimbus on 7/13/26.
//

#ifndef LITTLE_PROGRAM_STATE_H
#define LITTLE_PROGRAM_STATE_H


#include <array>
#include "Discrete_point.h"

struct State {
    State ();
    explicit State (const std::array<Discrete_point, 3>& points);

    std::array<Discrete_point, 3> p;
    long g;
    long f;
};


#endif //LITTLE_PROGRAM_STATE_H
