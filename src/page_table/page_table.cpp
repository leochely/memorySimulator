/**
 * This file contains implementations for methods in the PageTable class.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "page_table/page_table.h"
#include <climits>

using namespace std;


size_t PageTable::get_present_page_count() const {
  int sum = 0;
  for(auto &row: rows){
    if(row.present) sum++;
  }
  return sum;
}


size_t PageTable::get_oldest_page() const {
    int oldest = INT_MAX;
    int index = -1;
    for(int i = 0; i < rows.size(); ++i){
        if(rows[i].loaded_at < oldest && rows[i].loaded_at != -1 && rows[i].present){
            oldest = rows[i].loaded_at;
            index = i;
        }
    }
    return index;
}


size_t PageTable::get_least_recently_used_page() const {
    int oldest = INT_MAX;
    int index = -1;
    for(int i = 0; i < rows.size(); ++i){
        if(rows[i].last_accessed_at < oldest && rows[i].last_accessed_at != -1 && rows[i].present){
            oldest = rows[i].last_accessed_at;
            index = i;
        }
    }
  return index;
}
