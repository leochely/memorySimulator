/**
 * This file contains implementations for methods in the VirtualAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "virtual_address/virtual_address.h"
#include <string>
#include <bitset>

using namespace std;


VirtualAddress VirtualAddress::from_string(int process_id, string address) {
  bitset<PAGE_BITS> p(address.substr(0, PAGE_BITS));
  int page = (int)(p.to_ulong());
  bitset<OFFSET_BITS> off(address.substr(PAGE_BITS));
  int offset = (int)(off.to_ulong());
  return VirtualAddress(process_id, page, offset);
}


string VirtualAddress::to_string() const {
    bitset<PAGE_BITS> p(page);
    bitset<OFFSET_BITS> off(offset);
  return p.to_string() + off.to_string();
}


ostream& operator <<(ostream& out, const VirtualAddress& address) {
  out << "PID " << address.process_id
         << " @ " << address.to_string()
         << " [page: " << address.page
         << "; offset: " << address.offset
         << "]";
  return out;
}
