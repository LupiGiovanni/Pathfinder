//
// Created by gionimbus on 7/17/26.
//

#include "Simulation.h"
#include "Board_set.h"

Simulation::Simulation () {
    reset_fields();
}

void Simulation::reset_fields () {
    Asterism zero;
    start = zero;
    start_valid = false;
    destination = zero;
    destination_valid = false;
    destination_reached = false;
    distance_from_destination = std::numeric_limits<double>::infinity();
    collision_detected = false;
    fov_small_vignette_detected = false;
    fov_large_vignette_detected = false;
    duration = 0.;
    iterations = 0;
    max_iterations_exceeded = false;
}

void Simulation::run (const std::vector<Asterism>& aligned_path) {
    reset_fields();

    if ( aligned_path.empty() ) {
        std::cerr << "Warning: attempted to execute Simulation::run but 'path' is empty" << std::endl;
        return;
    }

    start = aligned_path.front();
    destination = aligned_path.back();

    start_valid = start.is_valid();
    destination_valid = destination.is_valid();

    if ( !start_valid || !destination_valid ) {
        std::cerr << "Warning: attempted to execute Simulation::run but 'path' start or destination are not valid" << std::endl;
        return;
    }

    Board_set bs;
    bs.teleport( aligned_path.front() );

    for (size_t i = 1; i < aligned_path.size(); i++) {
        if ( collision_detected )
            break;

        while ( !bs.is_destination_reached( aligned_path[i] ) && !collision_detected && iterations <= MAX_ITERATIONS ) {
            bs.step_move( aligned_path[i] );

            if ( bs.detect_collision(false) )
                collision_detected = true;
            if ( bs.detect_vignette_fov_small(false) )
                fov_small_vignette_detected = true;
            if ( bs.detect_vignette_fov_large(false) )
                fov_large_vignette_detected = true;

            iterations += 1;
        }
    }

    duration = SIMULATION_TIME_STEP * iterations;

    if ( collision_detected ) {
        std::cerr << "---------------------------------------------------------------------\n";
        std::cerr << "Warning: collision detected in running simulation from start asterism\n\n";
        aligned_path.front().print(true);
        std::cerr << "\nto destination asterism\n\n";
        aligned_path.back().print(true);
        std::cerr << "---------------------------------------------------------------------\n";
    }

    if ( bs.is_destination_reached( aligned_path.back() ) )
        destination_reached = true;
    distance_from_destination = bs.calculate_distance( aligned_path.back() );

    if ( iterations > MAX_ITERATIONS )
    max_iterations_exceeded = true;
}

void Simulation::print_results () const {
    std::cout << "\n---------------------------------------------------------------------------------------------------------\n";

    std::cout << "> Start asterism\t\t\t";
    start.print();
    std::cout << "> Start valid\t\t\t\t" << (start_valid? "true\n":"false\n");
    std::cout << "> Destination asterism\t\t";
    destination.print();
    std::cout << "> Destination valid\t\t\t" << (destination_valid? "true\n\n":"false\n\n");

    std::cout << "> Boards cruise velocity\t" << BOARDS_CRUISE_VELOCITY << " mm/s\n";
    std::cout << "> Movement duration\t\t\t" << duration << " s\n";
    std::cout << "> Simulation iterations\t\t" << iterations << "\n";
    std::cout << "> Max iterations exceeded\t" << (max_iterations_exceeded? "true\n":"false\n");
    std::cout << "> Simulation time step\t\t" << SIMULATION_TIME_STEP << " s\n";
    std::cout << "> Destination reached\t\t" << (destination_reached? "true\n":"false\n");
    std::cout << "> Distance from dest\t\t" << distance_from_destination << " mm\n";
    std::cout << "> Collision detected\t\t" << (collision_detected? "true\n":"false\n");
    std::cout << "> FoV small vignetting\t\t" << (fov_small_vignette_detected? "true\n":"false\n");
    std::cout << "> FoV large vignetting\t\t" << (fov_large_vignette_detected? "true\n":"false\n");

    std::cout << "---------------------------------------------------------------------------------------------------------\n\n";
}