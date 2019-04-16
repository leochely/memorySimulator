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
    string file;

    FlagOptions flagOptions;
    if(!parse_flags(argc, argv, flagOptions)){
        return -1;
    }

    vector<Process*> processes;
    vector<VirtualAddress> addresses;

    ifstream input(file);

    int numProcesses;
    input >> numProcesses;

    for(int i = 0; i < numProcesses; ++i){
        int tempID;
        string tempFile;

        input >> tempID;
        input >> tempFile;

        ifstream tempProcessFile(tempFile);
        Process* tempProcess = Process::read_from_input(tempProcessFile);

        processes.push_back(tempProcess);
    }

    for(auto& process : processes){
        cout << process << endl;
    }

    while(input.peek() != EOF){
        int pid;
        string address;

        input >> pid;
        input >> address;

        VirtualAddress tempAddress = VirtualAddress::from_string(pid, address);
        addresses.push_back(tempAddress);
        cout << tempAddress << endl;
    }



    return EXIT_SUCCESS;
}
