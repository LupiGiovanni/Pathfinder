#include "Asterism.h"
#include "A_star.h"

int main () {
    Asterism start (113.49709,-92.61197,75.734436,143.14001,173.01338,-177.28346);
    Asterism goal (215.5604,-191.21825,27.321161,-77.286896,78.6281,-215.80367);

    A_star astar;
    std::vector<Asterism> path = astar.search(start, goal);

    for (const auto& asterism : path) {
        for (const auto& point : asterism.p) {
            std::cout << "(" << point.x() << ", " << point.y() << ") ";
        }
        std::cout << std::endl;
    }
}