//
// Created by gionimbus on 7/13/26.
//

#include "Board_set.h"
#include "CAD_coordinates.h"

Board_set::Board_set () : boards{ Board(Board_type::board_0), Board(Board_type::board_1), Board(Board_type::board_2) }{
    fov_large.push_back(CAD_coordinates::R0);
    fov_large.push_back(CAD_coordinates::S0);
    fov_large.push_back(CAD_coordinates::T0);
    fov_large.push_back(CAD_coordinates::U0);

    fov_small.push_back(CAD_coordinates::R1);
    fov_small.push_back(CAD_coordinates::S1);
    fov_small.push_back(CAD_coordinates::T1);
    fov_small.push_back(CAD_coordinates::U1);

    constexpr double technical_field_radius_squared = TECHNICAL_FIELD_RADIUS * TECHNICAL_FIELD_RADIUS;
    technical_field = Circle (Point(0., 0.), technical_field_radius_squared);

    // Note that we do not need to rotate fov_small, fov_large and technical field because they are already aligned
    // with our reference system
}

bool Board_set::detect_collision () const {
    if ( CGAL::do_intersect(boards[0].profile_buffered, boards[1].profile_buffered) ||
         CGAL::do_intersect(boards[1].profile_buffered, boards[2].profile_buffered) ||
         CGAL::do_intersect(boards[0].profile_buffered, boards[2].profile_buffered) )
        return true;

    return false;
}

bool Board_set::detect_vignette_fov_small () const {
    for (const auto& board : boards)
        if (CGAL::do_intersect(board.profile_buffered, fov_small))
            return true;

    return false;
}

bool Board_set::detect_vignette_fov_large () const {
    for (const auto& board : boards)
        if (CGAL::do_intersect(board.profile_buffered, fov_large))
            return true;

    return false;
}

bool Board_set::align (Asterism& destination) {
    Board_set temporary;

    constexpr int permutations_count = 6;
    const std::vector<std::vector<int>> permutations = {
        {0, 1, 2},
        {0, 2, 1},
        {1, 0, 2},
        {1, 2, 0},
        {2, 0, 1},
        {2, 1, 0}
    };

    std::vector< std::pair< std::vector<int>, double > > targets_distance_vector = {};

    for (int i = 0; i < permutations_count; i++)
        if ( temporary.boards[0].teleport( destination.p[ permutations[i][0] ] ) &&
             temporary.boards[1].teleport( destination.p[ permutations[i][1] ] ) &&
             temporary.boards[2].teleport( destination.p[ permutations[i][2] ] ) &&
             ! temporary.detect_collision() )
        {
            temporary = *this;
            targets_distance_vector.push_back( std::make_pair( permutations[i], temporary.calculate_distance( destination, permutations[i] ) ) );
        }

    if ( targets_distance_vector.empty() )
        return false;

    auto min_element = std::ranges::min_element(targets_distance_vector,
            [](const std::pair< std::vector<int>, double >& a, const std::pair< std::vector<int>, double >& b) { return a.second < b.second; });

    std::vector<int> targets = min_element->first;

    Asterism swapped;
    for (int i = 0; i < 3; i++)
        swapped.p[i] = destination.p[ targets[i] ];

    destination = swapped;
    return true;
}

bool Board_set::align (Asterism& start, Asterism& destination) {
    Board_set temporary;
    temporary.teleport_home();
    if ( !temporary.align(start) )
        return false;
    temporary.teleport(start);
    if ( !temporary.align(destination) )
        return false;
    return true;
}

double Board_set::calculate_distance (const Asterism& destination, const std::vector<int>& targets) const {
    double distance = 0;

    for (int i = 0; i < 3; i++)
        distance += boards[i].calculate_distance( destination.p[ targets[i] ] );

    return distance;
}

double Board_set::calculate_distance (const Asterism& aligned_destination) const {
    double distance = 0;

    for (int i = 0; i < 3; i++)
        distance += boards[i].calculate_distance( aligned_destination.p[i] );

    return distance;
}

void Board_set::teleport (const Asterism& aligned_destination) {
    for (int j = 0; j < 3; j++)
        boards[j].teleport( aligned_destination.p[j] );
}

void Board_set::teleport_home () {
    for (int j = 0; j < 3; j++)
        boards[j].teleport_home();
}

void Board_set::step_move (const Asterism& aligned_destination) {
        for (int j = 0; j < 3; j++)
            boards[j].step_move( aligned_destination.p[j] );
}

bool Board_set::is_destination_in_range (const Asterism& aligned_destination) const {
    for (int j = 0; j < 3; j++)
        if ( ! boards[j].is_point_in_pom_range( aligned_destination.p[j] ) )
            return false;

    return true;
}

bool Board_set::is_destination_reached (const Asterism& aligned_destination, double tolerance) const {
    for (int j = 0; j < 3; j++)
        if ( ! boards[j].is_destination_reached( aligned_destination.p[j], tolerance) )
            return false;

    return true;
}