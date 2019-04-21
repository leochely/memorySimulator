/**
 * This file contains implementations for the methods defined in the Simulation
 * class.
 *
 * You'll probably spend a lot of your time here.
 */

#include "simulation/simulation.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include "flag_parser/flag_parser.h"
#include "virtual_address/virtual_address.h"
#include "physical_address/physical_address.h"
#include <fstream>

using namespace std;


void Simulation::run(FlagOptions flagOptions) {
    flags  = flagOptions;
    vector<VirtualAddress> addresses;

    ifstream input(flagOptions.filename);

    int numProcesses;
    input >> numProcesses;

    for(int i = 0; i < numProcesses; ++i){
        int tempID;
        string tempFile;

        input >> tempID;
        input >> tempFile;

        ifstream tempProcessFile(tempFile);
        Process* tempProcess = Process::read_from_input(tempProcessFile);
        processes.emplace(tempID, tempProcess);
    }

    int pid;
    string address;
    while (input >> pid) {
        input >> address;
        VirtualAddress tempAddress = VirtualAddress::from_string(pid, address);
        addresses.push_back(tempAddress);
        if(flagOptions.verbose) cout << tempAddress << endl;
        perform_memory_access(tempAddress);
        virtual_time++;
    }

    cout << "DONE!" << endl << endl;

    size_t memAccesses = 0;
    size_t faults = 0;
    size_t usedFrames = 0;
    for(auto &[pid, process]: processes){
        cout << "Process " <<  pid << ": ACCESSES: " << process->memory_accesses << " FAULTS: " << process->page_faults << " FAULT RATE: " << fixed << setprecision(2) << process->get_fault_percent() << " \tRSS: " << process->get_rss() << endl;
        memAccesses += process->memory_accesses;
        faults += process->page_faults;
        usedFrames += process->get_rss();
    }

    cout << "Total memory accesses:\t" << memAccesses << endl;
    cout << "Total page faults:\t" << faults << endl;
    cout << "Free frames remaining:\t" << NUM_FRAMES - usedFrames<< endl;

}


char Simulation::perform_memory_access(const VirtualAddress& address) {
    handle_page_fault(processes[address.process_id], address.page);
    int frame = processes[address.process_id]->page_table.rows[address.page].frame;
    PhysicalAddress physicalAddress(frame, address.offset);
    if(flags.verbose) cout << "  -> physical address " << physicalAddress << endl <<  "  -> RSS: " << processes[address.process_id]->get_rss() << endl << endl;
    return('f');
}


void Simulation::handle_page_fault(Process* process, size_t page) {
    process->memory_accesses +=1;
    if(process->page_table.rows[page].present){
        if(flags.verbose) cout << "  -> IN MEMORY" << endl;
        process->page_table.rows[page].last_accessed_at = virtual_time;
    }
    else{
        process->page_faults += 1;
        if(flags.verbose) cout << "  -> PAGE FAULT" <<endl;
        if(process->is_valid_page(page)){
            if(process->page_table.rows[page].loaded_at == -1 && process->get_rss() < flags.max_frames){
                process->page_table.rows[page].frame = frame_num;
                frame_num++;
            }
            else if(flags.strategy == ReplacementStrategy::FIFO){
                size_t toReplace = process->page_table.get_oldest_page();
                process->page_table.rows[toReplace].present = false;
                process->page_table.rows[page].frame = process->page_table.rows[toReplace].frame;
            }
            else{
                size_t toReplace = process->page_table.get_least_recently_used_page();
                process->page_table.rows[toReplace].present = false;
                process->page_table.rows[page].frame = process->page_table.rows[toReplace].frame;
            }
            process->page_table.rows[page].present = true;
            process->page_table.rows[page].loaded_at = virtual_time;
            process->page_table.rows[page].last_accessed_at = virtual_time;
        }
    }
}