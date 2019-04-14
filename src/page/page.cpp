/**
 * This file contains implementations for methods in the Page class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page/page.h"

using namespace std;


// Ensure PAGE_SIZE is initialized.
const size_t Page::PAGE_SIZE;


Page* Page::read_from_input(std::istream& in) {
  char c;
  if(in.peek() == EOF){
    return nullptr;
  }
  vector<char> temp;
  int count = 0;
  while(count < PAGE_SIZE && in.peek() != EOF ){
    count++;
    in.get(c);
    temp.push_back(c);
  }

  Page * page = new Page(temp);
  return page;
}


size_t Page::size() const {
  return bytes.size();
}


bool Page::is_valid_offset(size_t offset) const {
  return (offset<bytes.size());
}


char Page::get_byte_at_offset(size_t offset) {
  return bytes[offset];
}
