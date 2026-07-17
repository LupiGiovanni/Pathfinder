#include <chrono>

#include "Asterism.h"
#include "A_star.h"
#include "datasets.h"
#include "Simulation.h"

int main () {
    A_star astar;
    Simulation sim;
    std::vector<Asterism> path;
    // std::chrono::high_resolution_clock::time_point start_time, end_time;
    // std::chrono::duration<double> elapsed_time;
    // double total = 0;
    //
    // for (size_t i = 0; i < cedric_dataset.size() - 1; i++) {
    //
    //     start_time = std::chrono::high_resolution_clock::now();
    //     path = astar.search ( cedric_dataset[ i ], cedric_dataset[ i+1 ] );
    //     end_time = std::chrono::high_resolution_clock::now();
    //
    //     elapsed_time = end_time - start_time;
    //     total += elapsed_time.count();
    //
    //     if ( path.empty() )
    //         std::cout << "Failed" << std::endl;
    // }
    //
    // std::cout << "Average search time: " << total / static_cast<double>(cedric_dataset.size() - 1) << " seconds" << std::endl;

    path = astar.search ( cedric_dataset[ 0 ], cedric_dataset[ 15 ] );
    for (const auto& asterism : path) {
        asterism.print();
    }

    sim.run(path);
    sim.print_results();

    return 0;
}
