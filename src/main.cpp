/**
 * This file contains the main() function that drives the simulation. You'll
 * need to add logic to this file to create a Simulation instance and invoke its
 * run() method.
 */

#include <iostream>
#include <cstdlib>
#include <vector>
#include "flag_parser/flag_parser.h"
#include "simulation/simulation.h"
#include "virtual_address/virtual_address.h"
#include <fstream>

using namespace std;

/**
 * The main entry point to the simulation.
 */
int main(int argc, char** argv) {

    FlagOptions flagOptions;
    if(!parse_flags(argc, argv, flagOptions)){
        return -1;
    }

    Simulation simulation;
    simulation.run(flagOptions);

    return EXIT_SUCCESS;
}
