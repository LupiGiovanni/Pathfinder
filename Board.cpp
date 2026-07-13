//
// Created by gionimbus on 7/13/26.
//

#include "Board.h"
#include "CAD_coordinates.h"

Board::Board(Board_type t): velocity(BOARDS_CRUISE_VELOCITY), type(t) {
    if (t == Board_type::board_0) {
        profile.push_back(CAD_coordinates::A0);
        profile.push_back(CAD_coordinates::B0);
        profile.push_back(CAD_coordinates::C0);
        profile.push_back(CAD_coordinates::D0);
        profile.push_back(CAD_coordinates::E0);
        profile.push_back(CAD_coordinates::F0);
        profile.push_back(CAD_coordinates::G0);
        profile.push_back(CAD_coordinates::H0);
        profile.push_back(CAD_coordinates::I0);
        profile.push_back(CAD_coordinates::J0);
        profile.push_back(CAD_coordinates::K0);
        profile.push_back(CAD_coordinates::L0);

        pom_position = CAD_coordinates::M0;
        pom_home_position = CAD_coordinates::M0;

        pom_range.push_back(CAD_coordinates::N0);
        pom_range.push_back(CAD_coordinates::O0);
        pom_range.push_back(CAD_coordinates::P0);
        pom_range.push_back(CAD_coordinates::Q0);

        pom_safe_zone.push_back(CAD_coordinates::N0);
        pom_safe_zone.push_back(CAD_coordinates::V0);
        pom_safe_zone.push_back(CAD_coordinates::W0);
        pom_safe_zone.push_back(CAD_coordinates::Q0);
    }

    else if (t == Board_type::board_1) {
        profile.push_back(CAD_coordinates::A1);
        profile.push_back(CAD_coordinates::B1);
        profile.push_back(CAD_coordinates::C1);
        profile.push_back(CAD_coordinates::D1);
        profile.push_back(CAD_coordinates::E1);
        profile.push_back(CAD_coordinates::F1);
        profile.push_back(CAD_coordinates::G1);
        profile.push_back(CAD_coordinates::H1);
        profile.push_back(CAD_coordinates::I1);
        profile.push_back(CAD_coordinates::J1);
        profile.push_back(CAD_coordinates::K1);
        profile.push_back(CAD_coordinates::L1);

        pom_position = CAD_coordinates::M1;
        pom_home_position = CAD_coordinates::M1;

        pom_range.push_back(CAD_coordinates::N1);
        pom_range.push_back(CAD_coordinates::O1);
        pom_range.push_back(CAD_coordinates::P1);
        pom_range.push_back(CAD_coordinates::Q1);

        pom_safe_zone.push_back(CAD_coordinates::N1);
        pom_safe_zone.push_back(CAD_coordinates::V1);
        pom_safe_zone.push_back(CAD_coordinates::W1);
        pom_safe_zone.push_back(CAD_coordinates::Q1);
    }

    else if (t == Board_type::board_2) {
        profile.push_back(CAD_coordinates::A2);
        profile.push_back(CAD_coordinates::B2);
        profile.push_back(CAD_coordinates::C2);
        profile.push_back(CAD_coordinates::D2);
        profile.push_back(CAD_coordinates::E2);
        profile.push_back(CAD_coordinates::F2);
        profile.push_back(CAD_coordinates::G2);
        profile.push_back(CAD_coordinates::H2);
        profile.push_back(CAD_coordinates::I2);
        profile.push_back(CAD_coordinates::J2);
        profile.push_back(CAD_coordinates::K2);
        profile.push_back(CAD_coordinates::L2);

        pom_position = CAD_coordinates::M2;
        pom_home_position = CAD_coordinates::M2;

        pom_range.push_back(CAD_coordinates::N2);
        pom_range.push_back(CAD_coordinates::O2);
        pom_range.push_back(CAD_coordinates::P2);
        pom_range.push_back(CAD_coordinates::Q2);

        pom_safe_zone.push_back(CAD_coordinates::N2);
        pom_safe_zone.push_back(CAD_coordinates::V3);
        pom_safe_zone.push_back(CAD_coordinates::W3);
        pom_safe_zone.push_back(CAD_coordinates::Q2);
    }

    profile_buffered = enlarge(profile, BOARD_PROFILE_BUFFER_WIDTH);

    // Rotation is needed to align the CAD reference system with ours
    rotate(profile, M_PI / 2.);
    rotate(profile_buffered, M_PI / 2.);
    rotate(pom_position, M_PI / 2.);
    rotate(pom_home_position, M_PI / 2.);
    rotate(pom_range, M_PI / 2.);
    rotate(pom_safe_zone, M_PI / 2.);
}

bool Board::teleport (double pom_position_delta_x, double pom_position_delta_y) {
    const Vector displacement (pom_position_delta_x, pom_position_delta_y);
    const Point destination = pom_position + displacement;

    if (! is_point_in_pom_range(destination) )
        return false;

    for ( auto& point : profile )
        point += displacement;
    for ( auto& point : profile_buffered )
        point += displacement;

    pom_position = destination;

    return true;
}

bool Board::teleport (const Point& pom_destination) {
    return teleport (pom_destination.x() - pom_position.x(), pom_destination.y() - pom_position.y());
}

void Board::teleport_home () {
    teleport(pom_home_position);
}

bool Board::step_move(const Point& pom_destination) {
    if ( is_destination_reached(pom_destination) )
        return false;

    double distance_step = velocity * SIMULATION_TIME_STEP;
    Vector displacement (pom_destination - pom_position);
    double displacement_length = std::sqrt(displacement.squared_length());
    Vector step_vector = (displacement / displacement_length) * distance_step;
    teleport (pom_position + step_vector);

    return true;
}

bool Board::is_point_in_pom_range (const Point& point) const {
    if (pom_range.bounded_side(point) == CGAL::ON_BOUNDED_SIDE || pom_range.bounded_side(point) == CGAL::ON_BOUNDARY)
        return true;
    return false;
}

bool Board::is_destination_reached (const Point& pom_destination, double tolerance) const {
    Vector displacement (pom_destination - pom_position);
    if ( displacement.squared_length() <= tolerance * tolerance )
        return true;
    return false;
}

double Board::calculate_distance (const Point& pom_destination) const {
    Vector displacement (pom_destination - pom_position);
    return std::sqrt(displacement.squared_length());
}
