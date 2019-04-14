/**
 * This file contains the main() function that drives the simulation. You'll
 * need to add logic to this file to create a Simulation instance and invoke its
 * run() method.
 */

#include <cstdlib>
#include <vector>
#include "flag_parser/flag_parser.h"
#include "simulation/simulation.h"
#include <fstream>

using namespace std;

/**
 * The main entry point to the simulation.
 */
int main(int argc, char** argv) {
    string file;

    FlagOptions flagOptions;
    parse_flags(argc, argv, flagOptions);

    ifstream input(file);

    int numProcesses;
    input >> numProcesses;

    vector<int> processesID;
    vector<string> processesFiles;

    for(int i = 0; i < numProcesses; ++i){
        int tempID;
        string tempFile;

        input >> tempID;
        input >> tempFile;

        processesID.push_back(tempID);
        processesFiles.push_back(tempFile);
    }





    Simulation simulation;
    simulation.run();

    return EXIT_SUCCESS;
}
