/*
 * Config.cpp
 *
 *  Created on: Apr 25, 2018
 *      Author: nazgee
 */

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdexcept>
#include <errno.h>
#include <stdlib.h>

#include "Config.h"

Config::Config(int argc, char **argv) {
    int c;

    while (1) {
        static struct option long_options[] = {
            // These options set a flag.
            { "verbose", no_argument, &mSilent, 1 },
            // These options don't set a flag.
            //  We distinguish them by their indices.
            { "tutorial", required_argument, NULL, 't' },
            { 0, 0, 0, 0 }
        };

        // getopt_long stores the option index here.
        int option_index = 0;

        c = getopt_long(argc, argv, "d:b:p:t:", long_options, &option_index);

        // Detect the end of the options.
        if (c == -1)
            break;

        switch (c) {
            case 0: {
                // If this option set a flag, do nothing else now.
                if (long_options[option_index].flag != 0)
                    break;
                std::cout << "option " << long_options[option_index].name;
                if (optarg)
                    std::cout << " with arg " << optarg;
                std::cout << std::endl;
            }
            break;
            case 't': {
                mTutorial = optarg;
            }
            break;
            default: {
                abort();
            }
            break;
        }
    }

    // Print any remaining command line arguments (not options).
    if (optind < argc) {
        std::cerr << "non-option ARGV-elements: ";
        while (optind < argc)
            std::cerr << argv[optind++];
        std::cerr << std::endl;
    }
}

std::string Config::toString() {
    std::string ret = "silent=" + std::to_string(mSilent);
    ret += "\ntutorial=" + mTutorial;
    return ret;
}

Config::~Config() {
}

