//
// Created by gionimbus on 7/13/26.
//

#include <queue>
#include <limits>
#include "A_star.h"

#include "helper.h"

std::vector<Asterism> A_star::search (Asterism& start, Asterism& goal) {
    Board_set board_set;
    if (!board_set.align(start, goal))
        return {};

    State start_state = convert(start);
    State goal_state = convert(goal);

    std::vector<State> state_path = search(start_state, goal_state);
    std::vector<Asterism> asterism_path;
    for (const auto& state : state_path)
        asterism_path.push_back(convert(state));

    return asterism_path;
}

//TODO: is necessary to also add closed se or a check for already visited states?
std::vector<State> A_star::search (State& start, const State& goal) {
    Board_set board_set;
    std::priority_queue<State, std::vector<State>, State_comparator> frontier;
    std::unordered_map<State, State, State_hasher, State_equal> came_from;
    std::unordered_map<State, long, State_hasher, State_equal> g_so_far;
    came_from.reserve(1 << 16);
    g_so_far.reserve(1 << 16);

    start.g = 0;
    start.f = estimate_distance(start, goal);
    g_so_far[start] = 0;
    frontier.push(start);

    State current;
    long g_candidate;

    while (! frontier.empty() ) {
        current = frontier.top();
        frontier.pop();

        if ( is_goal_reached(current, goal) )
            return reconstruct_path(came_from, current);

        std::vector<State> next_states = get_next_states(current, goal, board_set);

        for ( auto& s : next_states ) {
            g_candidate = current.g + 10000; //TODO: change this magic number

            if ( !g_so_far.contains(s) || g_candidate < g_so_far[s] ) {
                g_so_far[s] = g_candidate;
                s.g = g_candidate;
                s.f = s.g + estimate_distance(s, goal);
                came_from[s] = current;
                frontier.push(s);
            }
        }
    }

    return {};
}

long A_star::estimate_distance (const State& current, const State& goal) {
    long x_local_current;
    long y_local_current;

    long x_local_goal;
    long y_local_goal;

    long total = 0;

    for (int i = 0; i < 3; i++) {
        x_local_current = transform_to_x_local(current.p[i].x, current.p[i].y, i);
        y_local_current = transform_to_y_local(current.p[i].x, current.p[i].y, i);

        x_local_goal = transform_to_x_local(goal.p[i].x, goal.p[i].y, i);
        y_local_goal = transform_to_y_local(goal.p[i].x, goal.p[i].y, i);

        total += std::abs( x_local_current - x_local_goal ) + std::abs( y_local_current - y_local_goal );
    }

    return total; //TODO: rescaling, i.e. dividing by DISCRETE_CONVERSION_FACTOR?
}

bool A_star::is_goal_reached (const State& current, const State& goal) {
    long dx;
    long dy;

    for (int i = 0; i < 3; i++) {
        dx = std::abs( current.p[i].x - goal.p[i].x );
        dy = std::abs( current.p[i].y - goal.p[i].y );

        if (dx > GOAL_REACHED_TOLERANCE || dy > GOAL_REACHED_TOLERANCE)
            return false;
    }

    return true;
}

//TODO: check if conversion from long to double causes problems
bool A_star::is_valid_state (const State& state, Board_set& board_set) {
    Asterism a = convert (state);

    if ( ! board_set.is_destination_in_range(a) )
        return false;

    board_set.teleport(a);

    if constexpr ( FOV_OPTIONS == Fov_options::none )
        return ! board_set.detect_collision();
    if constexpr ( FOV_OPTIONS == Fov_options::fov_small_excluded )
        return ! board_set.detect_collision() && ! board_set.detect_vignette_fov_small();
    if constexpr ( FOV_OPTIONS == Fov_options::fov_large_excluded )
        return ! board_set.detect_collision() && ! board_set.detect_vignette_fov_large();
}

//TODO: is it necessary to forcefully stop a board when it has reached its goal?
std::vector<State> A_star::get_next_states (const State& current, const State& goal, Board_set& board_set) {
    std::vector<State> next_vector;
    State next;

    for (int i = 0; i < DIRECTIONS_COUNT; i++) {
        for (int j = 0; j < DIRECTIONS_COUNT; j++) {
            for (int k = 0; k < DIRECTIONS_COUNT; k++) {
                if (i == 0 && j == 0 && k == 0)
                    continue;

                next = current;
                next.p[0].x += DX[0][i] * SEARCH_GRID_SIZE;
                next.p[0].y += DY[0][i] * SEARCH_GRID_SIZE;
                next.p[1].x += DX[1][j] * SEARCH_GRID_SIZE;
                next.p[1].y += DY[1][j] * SEARCH_GRID_SIZE;
                next.p[2].x += DX[2][k] * SEARCH_GRID_SIZE;
                next.p[2].y += DY[2][k] * SEARCH_GRID_SIZE;

                if (is_valid_state(next, board_set)) {
                    next_vector.push_back(next);
                }
            }
        }
    }

    return next_vector;
}

std::vector<State> A_star::reconstruct_path (const std::unordered_map<State, State, State_hasher, State_equal>& came_from, const State& current) {
    std::vector<State> path = {current};
    State s = current;

    while ( came_from.contains(s) ) {
        s = came_from.at(s);
        path.push_back(s);
    }

    std::ranges::reverse(path);

    return path;
}
