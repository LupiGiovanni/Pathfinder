//
// Created by gionimbus on 7/13/26.
//

#include <limits>
#include "State.h"

State::State(): p { Discrete_point(0, 0), Discrete_point(0, 0), Discrete_point(0, 0) },
    g( std::numeric_limits<long>::max() ), f( std::numeric_limits<long>::max() ) {}

State::State (const std::array<Discrete_point, 3>& points): p(points),
    g( std::numeric_limits<long>::max() ), f( std::numeric_limits<long>::max() ) {}