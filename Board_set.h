//
// Created by gionimbus on 7/13/26.
//

#ifndef LITTLE_PROGRAM_BOARD_SET_H
#define LITTLE_PROGRAM_BOARD_SET_H


#include <array>
#include "Asterism.h"
#include "Board.h"

class Board_set {
public:
    Board_set ();

    bool detect_collision () const ;
    bool detect_vignette_fov_small () const;
    bool detect_vignette_fov_large () const;

    bool align (Asterism& destination);
    bool align (Asterism& start, Asterism& destination);

    double calculate_distance (const Asterism& destination, const std::vector<int>& targets) const;
    double calculate_distance (const Asterism& aligned_destination) const;

    void teleport (const Asterism& aligned_destination);
    void teleport_home ();

    void step_move (const Asterism& aligned_destination);

    bool is_destination_in_range (const Asterism& aligned_destination) const;
    bool is_destination_reached (const Asterism& aligned_destination, double tolerance = DESTINATION_REACHED_TOLERANCE) const;

private:
    std::array<Board, 3> boards;

    Circle technical_field;
    Polygon fov_small;
    Polygon fov_large;
};


#endif //LITTLE_PROGRAM_BOARD_SET_H
