#include <chrono>

#include "Asterism.h"
#include "A_star.h"
#include "datasets.h"

int main () {
    A_star astar;
    std::vector<Asterism> path;

    for (size_t i = 0; i < cedric_dataset.size() - 1; i++) {

        path = astar.search ( cedric_dataset[ i ], cedric_dataset[ i+1 ] );

        if ( path.empty() )
            std::cout << "Failed" << std::endl;
    }

    return 0;
}