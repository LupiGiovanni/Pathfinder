#include <chrono>

#include "Asterism.h"
#include "A_star.h"
#include "datasets.h"
#include "Simulation.h"

int main () {
    A_star astar;
    Simulation sim;
    std::vector<Asterism> path;
    double time_sum = 0.;
    int failed = 0;

    for (size_t i = 0; i < cedric_dataset.size() - 1; i++) {
        path = astar.search(cedric_dataset[i], cedric_dataset[i+1]);
        sim.run(path);
        time_sum += sim.duration;
        if (sim.collision_detected || !sim.destination_reached )
            failed++;
    }

    std::cout << "Average time: " << time_sum / (cedric_dataset.size() - 1) << std::endl;
    std::cout << "Failed: " << failed << std::endl;

    return 0;
}
