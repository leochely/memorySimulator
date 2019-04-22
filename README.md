# Léo Chely: Project 2

## List of files

* main.cpp: calls the flag parser and run the simulation
* simulation: parse the simulation and processes files then converts the virtual addresses to physical addres in order to perform memory access. Outputs the detailled memory accesses depending on verbose flag and swaps pages in memory depending on strategy flag
* flag_parser: reads the flags
* frame: not used
* page: holds a page content 
* page_table: holds pointer to page and keeps track of the frames
* physical_address: converts a frame and an offset to a physical address
* process: holds the page_table and a vector of pointers to Page
* simulation: runs the memory management simulation. Handles page faults and swaps pages in and out of memory
* virtual_address: reads the virtual address from a stream and format it properly

## Interesting features

Nothing special in this project needs to be highlighted.

## Time spent on the project

+/- 10h

## Belady's anomaly

Belady's anomaly occurs when, for a given memory access pattern, the page faults increases despite an increase in the maximum number of frames. This rule is not true for all memory access patterns and is more likely to be experienced with FIFO strategy.

To observe the Belady's anomaly with my program, you shoud run the following commands:

```bash
./mem-sim sim_2 --max-frames 3
./mem-sim sim_2 --max-frames 4
```
