/**
 * This file contains implementations for methods in the PhysicalAddress class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "physical_address/physical_address.h"
#include <bitset>

using namespace std;


string PhysicalAddress::to_string() const {
  std::bitset<FRAME_BITS> f(frame);
  std::bitset<OFFSET_BITS> off(offset);

  return f.to_string() + off.to_string();
}


ostream& operator <<(ostream& out, const PhysicalAddress& address) {
  out << address.to_string() << " [frame: " << address.frame << "; offset: " << address.offset << "]";
  return out;
}
