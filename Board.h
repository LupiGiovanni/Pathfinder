//
// Created by gionimbus on 7/13/26.
//

#ifndef LITTLE_PROGRAM_BOARD_H
#define LITTLE_PROGRAM_BOARD_H


#include "helper.h"

enum class Board_type { board_0, board_1, board_2 }; // See documentation for CAD reference

class Board {
    friend class Board_set;
    friend class Animation;

private:
    Polygon profile;
    Polygon profile_buffered;

    Point pom_position;
    Point pom_home_position;
    Polygon pom_range;
    Polygon pom_safe_zone;

    double velocity;
    Board_type type;

    explicit Board (Board_type t);

    bool teleport (double pom_position_delta_x, double pom_position_delta_y);
    bool teleport (const Point& pom_destination);
    void teleport_home ();

    bool step_move (const Point& pom_destination);

    bool is_point_in_pom_range (const Point& point) const;
    bool is_destination_reached (const Point& pom_destination, double tolerance = DESTINATION_REACHED_TOLERANCE) const;

    double calculate_distance (const Point& pom_destination) const;
};


#endif //LITTLE_PROGRAM_BOARD_H
