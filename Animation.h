//
// Created by gionimbus on 7/18/26.
//

#ifndef LITTLE_PROGRAM_ANIMATION_H
#define LITTLE_PROGRAM_ANIMATION_H

#include <SFML/Graphics.hpp>
#include "Board_set.h"


class Animation {
public:
    Animation ();
    void animate (const std::vector<Asterism>& aligned_path);

private:
    std::vector< sf::VertexArray > boards;
    std::vector< sf::VertexArray > trajectories;
    std::vector< sf::ConvexShape > pom_ranges;
    sf::ConvexShape fov_small;
    sf::ConvexShape fov_large;
    sf::CircleShape technical_field;
    std::vector<sf::CircleShape> start_asterism;
    std::vector<sf::CircleShape> destination_asterism;

    sf::Clock frame_clock;
    sf::Time frame_time;

    sf::Clock animation_start_clock;
    sf::Time animation_start_time;

    float convert_to_window_x (double x_coordinate) const;
    float convert_to_window_y (double y_coordinate) const;

    void setup_pom_ranges ();
    void setup_fov_large ();
    void setup_fov_small ();
    void setup_technical_field ();
    void setup_boards (const Board_set& board_set);
    void setup_start_asterism (const Asterism& asterism);
    void setup_destination_asterism (const Asterism& asterism);

    void clear_trajectories ();
    void update_trajectories (const Board_set& board_set);

    void rotate_clockwise_around_center (sf::ConvexShape& shape, float angle_degrees);
};


#endif //LITTLE_PROGRAM_ANIMATION_H
