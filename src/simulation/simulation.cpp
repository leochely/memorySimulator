/**
 * This file contains implementations for the methods defined in the Simulation
 * class.
 *
 * You'll probably spend a lot of your time here.
 */

#include "simulation/simulation.h"
#include "virtual_address/virtual_address.h"
using namespace std;


void Simulation::run() {

}


char Simulation::perform_memory_access(const VirtualAddress& address) {
    size_t frame;
    for(auto& process: processes){
      if(process->pid == address.process_id){
          return(process->pages[address.page]->get_byte_at_offset(address.offset));
      }
  }
}


void Simulation::handle_page_fault(Process* process, size_t page) {
    if(process->is_valid_page(page)){
        exit(1);
    }
}
