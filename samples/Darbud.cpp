/*
 * Darbud.cpp
 *
 *  Created on: Apr 25, 2018
 *      Author: nazgee
 */

#include <functional>
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <map>
#include <array>

#include "Darbud.h"

namespace Darbud {

std::string input = "aabcdaddbhda";

int main(int argc, char** argv) {
    std::cout << "running " << __PRETTY_FUNCTION__ << std::endl;

    std::map<char, int> hits;
    for (auto c : input) {
        std::cout << "char=" << c << std::endl;
        hits[c] += 1;
    }

    std::vector<std::pair<char, int>> result;
    result.reserve(hits.size());
    std::copy(hits.begin(), hits.end(), std::back_inserter(result));

    std::sort(result.begin(), result.end(),
            [](std::pair<char, int>& lhs, std::pair<char, int>& rhs){
                return lhs.second > rhs.second;
            }
    );

    std::cout << "===" << std::endl;

    std::for_each(result.begin(), result.end(), [](std::pair<char, int> p) {
        std::cout << p.first << "=" << p.second << std::endl;
    });

    return EXIT_SUCCESS;
}

}
