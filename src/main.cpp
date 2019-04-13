/**
 * This file contains the main() function that drives the simulation. You'll
 * need to add logic to this file to create a Simulation instance and invoke its
 * run() method.
 */

#include <cstdlib>
#include "flag_parser/flag_parser.h"
#include "simulation/simulation.h"

using namespace std;

/**
 * The main entry point to the simulation.
 */
int main(int argc, char** argv) {
    string file;

    FlagOptions flagOptions;
    parse_flags(argc, argv, flagOptions);

    ifstream input(file);



    Simulation simulation;
    simulation.run();

    return EXIT_SUCCESS;
}
