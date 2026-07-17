//
// Created by gionimbus on 7/17/26.
//

#ifndef LITTLE_PROGRAM_SIMULATION_H
#define LITTLE_PROGRAM_SIMULATION_H


#include "Asterism.h"

struct Simulation {
        Asterism start;
        bool start_valid;

        Asterism destination;
        bool destination_valid;
        bool destination_reached;
        double distance_from_destination;

        bool collision_detected;
        bool fov_small_vignette_detected;
        bool fov_large_vignette_detected;

        double duration; // s
        int iterations;
        bool max_iterations_exceeded;

        Simulation ();
        void reset_fields ();
        void run (const std::vector<Asterism>& aligned_path);
        void print_results () const;
};


#endif //LITTLE_PROGRAM_SIMULATION_H
