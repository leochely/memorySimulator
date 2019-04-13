/**
 * This file contains implementations for methods in the flag_parser.h file.
 *
 * You'll need to add code here to make the corresponding tests pass.
 */

#include "flag_parser/flag_parser.h"
#include <iostream>
#include <getopt.h>
using namespace std;


void print_usage() {
  cout <<
      "Usage: mem-sim [options] filename\n"
      "\n"
      "Options:\n"
      "  -v, --verbose\n"
      "      Output information about every memory access.\n"
      "\n"
      "  -s, --strategy (FIFO | LRU)\n"
      "      The replacement strategy to use. One of FIFO or LRU.\n"
      "\n"
      "  -f, --max-frames <positive integer>\n"
      "      The maximum number of frames a process may be allocated.\n"
      "\n"
      "  -h --help\n"
      "      Display a help message about these flags and exit\n"
      "\n";
}


bool parse_flags(int argc, char** argv, FlagOptions& flags) {
    int verbose = 0;
    int strategy = 0;
    int frames = 0;

    while(1){
        static struct option long_options[] =
                {
                        {"verbose", no_argument, &verbose, 'v'},
                        {"strategy", required_argument, &strategy, 's'},
                        {"max-frames", required_argument, &frames, 'f'},
                        {"help", no_argument, &help, 'h'},
                };

        int option_index = 0;

        int c = getopt_long (argc, argv, "vsfh:", long_options, &option_index);

        if(c == -1)
            break;

        switch(c){
            case 'v':
                verbose = 1;
                break;
            case 'h':
                help = 1;
                break;
            case 's':
                strategy= 1;
                strat = optarg;
                break;
            case 'f':
                frames = 1;
                maxFrames = optarg;
                break;
            default:
                abort();
        }
    }

    if(help){
        print_usage();
    }
    else{
        flags.filename = argv[-1];
        if(frames) flags.max_frames = maxFrames;
        if(strategy && strat == "LRU") flags.strategy = LRU;
        flags.verbose = verbose;
    }

  return true;
}
