//
// Created by gionimbus on 7/13/26.
//

#ifndef LITTLE_PROGRAM_HELPER_H
#define LITTLE_PROGRAM_HELPER_H


#include <CGAL/Simple_cartesian.h>
#include <CGAL/draw_polygon_set_2.h>
#include <CGAL/Aff_transformation_2.h>
#include <CGAL/approximated_offset_2.h>
#include <CGAL/Boolean_set_operations_2.h>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point;
typedef CGAL::Vector_2<Kernel> Vector;
typedef CGAL::Polygon_2<Kernel> Polygon;
typedef CGAL::Circle_2<Kernel> Circle;
typedef CGAL::Aff_transformation_2<Kernel> Transformation;

enum class Fov_options {none, fov_small_excluded, fov_large_excluded};
constexpr auto FOV_OPTIONS = Fov_options::none;

constexpr double SIMULATION_TIME_STEP = 0.05; // s
constexpr double TECHNICAL_FIELD_RADIUS = 265.2; // mm
constexpr double BOARD_PROFILE_BUFFER_WIDTH = 10.; // mm
constexpr double BOARDS_CRUISE_VELOCITY = 4.; // mm/s
constexpr double DESTINATION_REACHED_TOLERANCE = BOARDS_CRUISE_VELOCITY * SIMULATION_TIME_STEP; // mm

constexpr long GOAL_REACHED_TOLERANCE = 20000; // 1000 units == 1 mm
constexpr long SEARCH_GRID_SIZE = 10; // 10 * 1000 units
constexpr long TIE_BREAK = 100;
constexpr long WEIGHT = 2;

constexpr double CONVERSION_FACTOR_DOUBLE = 1000.; // *** DO NOT CHANGE! ***    1000 units == 1 mm
constexpr long CONVERSION_FACTOR_LONG = 1000; // *** DO NOT CHANGE! ***
constexpr long X_ORIGIN[3] = {284574, -402094, 117521};
constexpr long Y_ORIGIN[3] = {-300000, -96448, 396448};
constexpr long SIN30 = 500;
constexpr long COS30 = 866;
constexpr int DIRECTIONS_COUNT = 5;
constexpr long DX[3][5] =
{
    // {wait, up, down, right, left}
    {0,  1000,  -1000,   0,      0},     // board 0
    {0, -SIN30,  SIN30,  COS30, -COS30}, // board 1
    {0, -SIN30,  SIN30, -COS30,  COS30}  // board 2
};
constexpr long DY[3][5] =
{
    // {wait, up, down, right, left}
    {0,  0,      0,     -1000,   1000},  // board 0
    {0,  COS30, -COS30,  SIN30, -SIN30}, // board 1
    {0, -COS30,  COS30,  SIN30, -SIN30}  // board 2
};
constexpr long ROTATION_VALUES[3][2] =
{
    { 0,     -1000},    // board 0 ref system is rotated by -90 degrees
    { COS30,  SIN30},   // board 1 ref system is rotated by 30 degrees
    {-COS30,  SIN30}    // board 2 ref system is rotated by 150 degrees
};

// Helper functions
inline void rotate (Polygon& polygon, double angle_radians) {
    Transformation rotation (CGAL::ROTATION, std::sin(angle_radians), std::cos(angle_radians));
    for (auto& vertex : polygon)
        vertex = rotation.transform(vertex);
}

inline void rotate (Point& point, double angle_radians) {
    Transformation rotation (CGAL::ROTATION, std::sin(angle_radians), std::cos(angle_radians));
    point = rotation.transform(point);
}

//TODO: check if the function works correctly
inline Polygon enlarge (const Polygon& polygon, double offset) {
    Polygon p = polygon;
    if (p.is_clockwise_oriented())
        p.reverse_orientation();

    const double eps = 0.1;
    auto offset_poly_with_holes = CGAL::approximated_offset_2(p, offset, eps);

    Polygon enlarged_poly;
    auto outer = offset_poly_with_holes.outer_boundary();

    for (auto c = outer.curves_begin(); c != outer.curves_end(); ++c) {
        auto pt = c->source();
        enlarged_poly.push_back(Point(CGAL::to_double(pt.x()), CGAL::to_double(pt.y())));
    }

    return enlarged_poly;
}

inline long convert (double continuous_coordinate) {
    return std::lround( continuous_coordinate * CONVERSION_FACTOR_DOUBLE );
}

inline double convert (long discrete_coordinate) {
    return static_cast<double>( discrete_coordinate ) / CONVERSION_FACTOR_DOUBLE;
}

inline long transform_to_x_local (long x_global, long y_global,  int reference_system_id) {
    long x_origin = X_ORIGIN[reference_system_id];
    long y_origin = Y_ORIGIN[reference_system_id];
    long cos = ROTATION_VALUES[reference_system_id][0];
    long sin = ROTATION_VALUES[reference_system_id][1];

    long x_local = (x_global - x_origin) * cos + (y_global - y_origin) * sin;
    return (x_local >= 0) ? ( x_local + CONVERSION_FACTOR_LONG/2 ) / CONVERSION_FACTOR_LONG :
        ( x_local - CONVERSION_FACTOR_LONG/2 ) / CONVERSION_FACTOR_LONG;
}

inline long transform_to_y_local (long x_global, long y_global,  int reference_system_id) {
    long x_origin = X_ORIGIN[reference_system_id];
    long y_origin = Y_ORIGIN[reference_system_id];
    long cos = ROTATION_VALUES[reference_system_id][0];
    long sin = ROTATION_VALUES[reference_system_id][1];

    long y_local = (x_global - x_origin) * -sin + (y_global - y_origin) * cos;
    return (y_local >= 0) ? ( y_local + CONVERSION_FACTOR_LONG/2 ) / CONVERSION_FACTOR_LONG :
        ( y_local - CONVERSION_FACTOR_LONG/2 ) / CONVERSION_FACTOR_LONG;
}


#endif //LITTLE_PROGRAM_HELPER_H
