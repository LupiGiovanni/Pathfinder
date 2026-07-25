#include <chrono>

#include "Asterism.h"
#include "A_star.h"
#include "datasets.h"
#include "Simulation.h"
#include "Animation.h"

int main () {
    A_star astar;
    Simulation sim;
    Animation animator;
    std::vector<Asterism> path;

    for (size_t i = 0; i < cedric_dataset.size() - 1; i++) {
        path = astar.search(cedric_dataset[i], cedric_dataset[i + 1]);
        animator.animate(path);
    }

    return 0;
}
