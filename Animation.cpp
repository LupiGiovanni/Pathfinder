//
// Created by gionimbus on 7/18/26.
//

#include "Animation.h"
#include "CAD_coordinates.h"
#include "helper.h"

constexpr int BOARD_VERTICES_COUNT = 12;
constexpr int POM_RANGE_VERTICES_COUNT = 4;
constexpr int WINDOW_HEIGHT = 1000;
constexpr int WINDOW_WIDTH = 1000;
constexpr double ASTERISM_CIRCLE_RADIUS = 8.;
constexpr int CONVEX_SHAPES_TRANSPARENCY = 60;
constexpr int FRAME_TIME = 15; // milliseconds
constexpr int ANIMATION_START_TIME = 1000; // milliseconds

Animation::Animation () {
    for (int j = 0; j < 3; j++) {
        boards.push_back( sf::VertexArray(sf::LineStrip, BOARD_VERTICES_COUNT+1) );
        trajectories.push_back( sf::VertexArray(sf::Points) );
        pom_ranges.push_back( sf::ConvexShape(POM_RANGE_VERTICES_COUNT) );
        start_asterism.push_back( sf::CircleShape(ASTERISM_CIRCLE_RADIUS) );
        destination_asterism.push_back( sf::CircleShape(ASTERISM_CIRCLE_RADIUS) );
    }

    setup_pom_ranges();
    clear_trajectories();
    setup_fov_large();
    setup_fov_small();
    setup_technical_field();

    frame_time = sf::milliseconds( FRAME_TIME );
    animation_start_time = sf::milliseconds( ANIMATION_START_TIME );
}

float Animation::convert_to_window_x (double x_coordinate) const {
    return x_coordinate + WINDOW_WIDTH / 2.;
}

float Animation::convert_to_window_y (double y_coordinate) const {
    return -y_coordinate + WINDOW_HEIGHT / 2.;
}

void Animation::setup_pom_ranges () {
    pom_ranges[0].setPoint(0, sf::Vector2f(convert_to_window_x(CAD_coordinates::N0.x()), convert_to_window_y(CAD_coordinates::N0.y())));
    pom_ranges[0].setPoint(1, sf::Vector2f(convert_to_window_x(CAD_coordinates::O0.x()), convert_to_window_y(CAD_coordinates::O0.y())));
    pom_ranges[0].setPoint(2, sf::Vector2f(convert_to_window_x(CAD_coordinates::P0.x()), convert_to_window_y(CAD_coordinates::P0.y())));
    pom_ranges[0].setPoint(3, sf::Vector2f(convert_to_window_x(CAD_coordinates::Q0.x()), convert_to_window_y(CAD_coordinates::Q0.y())));
    pom_ranges[0].setOutlineThickness(0.);
    pom_ranges[0].setFillColor(sf::Color(255, 0, 0, CONVEX_SHAPES_TRANSPARENCY));

    pom_ranges[1].setPoint(0, sf::Vector2f(convert_to_window_x(CAD_coordinates::N1.x()), convert_to_window_y(CAD_coordinates::N1.y())));
    pom_ranges[1].setPoint(1, sf::Vector2f(convert_to_window_x(CAD_coordinates::O1.x()), convert_to_window_y(CAD_coordinates::O1.y())));
    pom_ranges[1].setPoint(2, sf::Vector2f(convert_to_window_x(CAD_coordinates::P1.x()), convert_to_window_y(CAD_coordinates::P1.y())));
    pom_ranges[1].setPoint(3, sf::Vector2f(convert_to_window_x(CAD_coordinates::Q1.x()), convert_to_window_y(CAD_coordinates::Q1.y())));
    pom_ranges[1].setOutlineThickness(0.);
    pom_ranges[1].setFillColor(sf::Color(0, 255, 0, CONVEX_SHAPES_TRANSPARENCY));

    pom_ranges[2].setPoint(0, sf::Vector2f(convert_to_window_x(CAD_coordinates::N2.x()), convert_to_window_y(CAD_coordinates::N2.y())));
    pom_ranges[2].setPoint(1, sf::Vector2f(convert_to_window_x(CAD_coordinates::O2.x()), convert_to_window_y(CAD_coordinates::O2.y())));
    pom_ranges[2].setPoint(2, sf::Vector2f(convert_to_window_x(CAD_coordinates::P2.x()), convert_to_window_y(CAD_coordinates::P2.y())));
    pom_ranges[2].setPoint(3, sf::Vector2f(convert_to_window_x(CAD_coordinates::Q2.x()), convert_to_window_y(CAD_coordinates::Q2.y())));
    pom_ranges[2].setOutlineThickness(0.);
    pom_ranges[2].setFillColor(sf::Color(0, 0, 255, CONVEX_SHAPES_TRANSPARENCY));

    for (auto& it : pom_ranges)
        rotate_clockwise_around_center(it, -90.f);
}

void Animation::setup_fov_large () {
    fov_large.setPointCount(4);
    fov_large.setPoint(0, sf::Vector2f(convert_to_window_x(CAD_coordinates::R0.x()), convert_to_window_y(CAD_coordinates::R0.y())));
    fov_large.setPoint(1, sf::Vector2f(convert_to_window_x(CAD_coordinates::S0.x()), convert_to_window_y(CAD_coordinates::S0.y())));
    fov_large.setPoint(2, sf::Vector2f(convert_to_window_x(CAD_coordinates::T0.x()), convert_to_window_y(CAD_coordinates::T0.y())));
    fov_large.setPoint(3, sf::Vector2f(convert_to_window_x(CAD_coordinates::U0.x()), convert_to_window_y(CAD_coordinates::U0.y())));
    fov_large.setOutlineThickness(0.);
    fov_large.setFillColor(sf::Color(255, 255, 255, CONVEX_SHAPES_TRANSPARENCY));
}

void Animation::setup_fov_small () {
    fov_small.setPointCount(4);
    fov_small.setPoint(0, sf::Vector2f(convert_to_window_x(CAD_coordinates::R1.x()), convert_to_window_y(CAD_coordinates::R1.y())));
    fov_small.setPoint(1, sf::Vector2f(convert_to_window_x(CAD_coordinates::S1.x()), convert_to_window_y(CAD_coordinates::S1.y())));
    fov_small.setPoint(2, sf::Vector2f(convert_to_window_x(CAD_coordinates::T1.x()), convert_to_window_y(CAD_coordinates::T1.y())));
    fov_small.setPoint(3, sf::Vector2f(convert_to_window_x(CAD_coordinates::U1.x()), convert_to_window_y(CAD_coordinates::U1.y())));
    fov_small.setOutlineThickness(0.);
    fov_small.setFillColor(sf::Color(255, 255, 255, CONVEX_SHAPES_TRANSPARENCY));
}

void Animation::setup_technical_field () {
    technical_field.setPointCount(100);
    technical_field.setRadius(TECHNICAL_FIELD_RADIUS);
    technical_field.setOrigin(TECHNICAL_FIELD_RADIUS, TECHNICAL_FIELD_RADIUS);
    technical_field.setPosition(convert_to_window_x(0.), convert_to_window_y(0.));
    technical_field.setOutlineThickness(0.);
    technical_field.setFillColor(sf::Color(255, 255, 255, CONVEX_SHAPES_TRANSPARENCY));
}

void Animation::setup_boards (const Board_set& board_set) {
    std::array<Board, 3> boards_vector = board_set.boards;

    for (int j = 0; j < 3; j++) {
        const Polygon& board_profile = boards_vector[j].profile;

        for (int i = 0; i < BOARD_VERTICES_COUNT; i++)
            boards[j][i].position = sf::Vector2f(convert_to_window_x(board_profile[i].x()), convert_to_window_y(board_profile[i].y()));

        boards[j][BOARD_VERTICES_COUNT].position = boards[j][0].position;
    }
}

void Animation::setup_start_asterism (const Asterism& asterism) {
    for (int j = 0; j < 3; j++) {
        start_asterism[j].setPointCount(100);
        start_asterism[j].setOrigin(ASTERISM_CIRCLE_RADIUS, ASTERISM_CIRCLE_RADIUS);
        start_asterism[j].setPosition(convert_to_window_x(asterism.p[j].x()), convert_to_window_y(asterism.p[j].y()));
        start_asterism[j].setOutlineThickness(2);
        start_asterism[j].setOutlineColor(sf::Color::Black);
        start_asterism[j].setFillColor(sf::Color::Green);
    }
}

void Animation::setup_destination_asterism (const Asterism& asterism) {
    for (int j = 0; j < 3; j++) {
        destination_asterism[j].setPointCount(100);
        destination_asterism[j].setOrigin(ASTERISM_CIRCLE_RADIUS, ASTERISM_CIRCLE_RADIUS);
        destination_asterism[j].setPosition(convert_to_window_x(asterism.p[j].x()), convert_to_window_y(asterism.p[j].y()));
        destination_asterism[j].setOutlineThickness(2);
        destination_asterism[j].setOutlineColor(sf::Color::Black);
        destination_asterism[j].setFillColor(sf::Color::Red);
    }
}

void Animation::clear_trajectories () {
    for (int j = 0; j < 3; j++)
        trajectories[j].clear();
}

void Animation::update_trajectories (const Board_set& board_set) {
    std::array<Board, 3> b = board_set.boards;

    for (int j = 0; j < 3; j++) {
        Point pom_pos = b[j].pom_position;
        sf::Vertex v;

        v.position = sf::Vector2f(convert_to_window_x(pom_pos.x()), convert_to_window_y(pom_pos.y()));
        v.color = sf::Color::Green;
        v.color.a = 255;

        trajectories[j].append(v);
    }
}

void Animation::rotate_clockwise_around_center (sf::ConvexShape& shape, float angle_degrees) {
    sf::Vector2f rotation_center(convert_to_window_x(0.), convert_to_window_y(0.));

    sf::Transform t;
    t.rotate(angle_degrees, rotation_center);

    sf::Vector2f new_position = t.transformPoint(shape.getPosition());

    shape.setPosition(new_position);
    shape.rotate(angle_degrees);
}

void Animation::animate (const std::vector<Asterism>& aligned_path) {
    if (aligned_path.empty()) {
        std::cout << "Warning: attempted to run Graphic_viewer::animate_A_star but 'path' is empty" << std::endl;
        return;
    }

    sf::RenderWindow window;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "", sf::Style::Close | sf::Style::Titlebar);

    Board_set temporary;
    Asterism current_destination;
    setup_start_asterism(aligned_path.front());
    setup_destination_asterism(aligned_path.back());

    while (window.isOpen()) {

        sf::Event event;

        if (animation_start_clock.getElapsedTime() >= animation_start_time) {
            int iterations = 0;
            bool collision_detected = false;
            clear_trajectories();
            temporary.teleport(aligned_path.front());

            for (int i = 2; i < aligned_path.size(); i++) {
                if (collision_detected)
                    break;

                current_destination = aligned_path[i];

                while ( ! temporary.is_destination_reached(current_destination) && ! collision_detected && iterations <= MAX_ITERATIONS ) {

                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                            window.close();
                            return;
                        }
                    }

                    if ( frame_clock.getElapsedTime() >= frame_time ) {
                        update_trajectories(temporary);
                        setup_boards(temporary);
                        window.clear(sf::Color::Black);
                        window.draw(technical_field);
                        window.draw(fov_large);
                        window.draw(fov_small);
                        for (int j = 0; j < 3; j++) {
                            window.draw(pom_ranges[j]);
                            window.draw(trajectories[j]);
                            window.draw(boards[j]);
                            window.draw(start_asterism[j]);
                            window.draw(destination_asterism[j]);
                        }
                        window.display();

                        temporary.step_move(current_destination);
                        if ( temporary.detect_collision(false) ) {
                            collision_detected = true;
                            std::cerr << "Collision detected while executing Simulation_animator::animate\n";
                        }
                        iterations += 1;
                        frame_clock.restart();
                    } else sf::sleep(sf::milliseconds(1));
                }
            }
            animation_start_clock.restart();
        } else sf::sleep(sf::milliseconds(10));
    }
}