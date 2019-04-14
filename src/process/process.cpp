/**
 * This file contains implementations for methods in the Process class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "process/process.h"
#include "page/page.h"

using namespace std;


Process* Process::read_from_input(std::istream& in) {
  vector<char> tempChar;
  Page* page = new Page(tempChar);
  size_t size = 0;
  vector<Page*> temp;
  while((page = page->read_from_input(in)) != nullptr){
    temp.push_back(page);
    size += page->size();
  }
  Process* process = new Process(size, temp);
  return process;
}


size_t Process::size() const {
  return num_bytes;
}


bool Process::is_valid_page(size_t index) const {
  return (index < pages.size());
}


size_t Process::get_rss() const {
  int count = 0;
  for(auto &row : page_table.rows){
    if(row.present) count++;
  }
  return count;
}


double Process::get_fault_percent() const {
  if(memory_accesses == 0.0) return 0.0;
  return (100* page_faults / memory_accesses);
}
