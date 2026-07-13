//
// Created by gionimbus on 7/13/26.
//

#ifndef LITTLE_PROGRAM_A_STAR_H
#define LITTLE_PROGRAM_A_STAR_H


#include <unordered_map>
#include <vector>
#include <iostream>
#include "State.h"
#include "Board_set.h"

class A_star {
public:
    A_star () = default;
    std::vector<Asterism> search (Asterism& start, Asterism& goal);

private:
    struct State_hasher {
        std::size_t operator () (const State& state) const {
            std::size_t h = 0;
            for (size_t i = 0; i < state.p.size(); i++) {
                std::size_t h1 = std::hash<long>{}(state.p[i].x);
                std::size_t h2 = std::hash<long>{}(state.p[i].y);
                h ^= h1 + 0x9e3779b9 + (h << 6) + (h >> 2);
                h ^= h2 + 0x9e3779b9 + (h << 6) + (h >> 2);
            }
            return h;
        }
    };

    struct State_equal {
        bool operator () (const State& first, const State& second) const {
            if (first.p.size() != second.p.size()) return false;
            for (size_t i = 0; i < first.p.size(); i++)
                if (first.p[i] != second.p[i]) return false;
            return true;
        }
    };

    struct State_comparator {
        bool operator () (const State& first, const State& second) const {
            return first.f > second.f;
        }
    };

    std::vector<State> search (State& start, const State& goal);
    long estimate_distance (const State& current, const State& goal);
    bool is_goal_reached (const State& current, const State& goal);
    bool is_valid_state (const State& state, Board_set& board_set);
    std::vector<State> get_next_states (const State& current, const State& goal, Board_set& board_set);
    std::vector<State> reconstruct_path (const std::unordered_map<State, State, State_hasher, State_equal>& came_from, const State& current);
};


#endif //LITTLE_PROGRAM_A_STAR_H
