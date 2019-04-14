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
    if (argc == 1 ){
        return false;
    }
    while(1){

        string strategyType = "";
        int frameNumber = 10;

        static struct option long_options[] ={

                {"verbose", no_argument, 0, 'v'},
                {"strategy", required_argument, 0, 's'},
                {"max-frames", required_argument,0, 'f'},
                {"help", no_argument, 0, 'h'},
                {0,0,0,0}
        };
        int option_index = 0;

        if (argv[argc-1] == "./mem-sim"){
            return false;
        }
        int flag = getopt_long(argc, argv, "-vs:f:h", long_options, &option_index);
        if(flag == -1){
            break;
        }
//		string temp = optarg;
        switch (flag){

            case 'v':
                flags.verbose = true;
                break;
            case 's':
                strategyType = optarg;
                if (strategyType == "FIFO"){
                    flags.strategy = ReplacementStrategy::FIFO;
                }else if(strategyType == "LRU"){
                    flags.strategy = ReplacementStrategy::LRU;
                }else{
                    //flags.strategy = ReplacementStrategy::FIFO; //unknown strategy uses FIFO
                    return false;
                }
                break;
            case 'f':

//				if (temp.find_first_not_of( "0123456789" ) != std::string::npos){
//					return false;
//				}
                frameNumber = stoi(optarg);
                if (frameNumber > 0){
                    flags.max_frames = frameNumber ;
                }else{
                    flags.max_frames = 10;
                    return false;
                }
                break;

            case 1:
                flags.filename = optarg;
                break;
            case 'h':

                print_usage();
                break;
            case '?':
            default:
                //print_usage();
                return false;

        }

    }

    return true;
}