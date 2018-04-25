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

    std::for_each(result.begin(), result.end(), [](std::pair<char, int> p) {
        std::cout << p.first << "=" << p.second << std::endl;
    });

    return EXIT_SUCCESS;
}

}

namespace Iwanodar {
int count(std::string str, char& ch) {
    return std::count(str.begin(), str.end(), ch);
}

int main(int argc, char** argv) {
    std::string input = "dmvkekocmppiorejcnoe";
    std::string pattern = "abcdefghijklmnoprstuvwxyz";

    std::vector<int> result;
    result.reserve(pattern.size());
    auto count_func = std::bind(&count, input, std::placeholders::_1);
    // XXX transform pattern string into results string, showing how often
    // particular char of pattern is present in input
    std::transform(pattern.begin(), pattern.end(), result.begin(), result.end(), count_func);

    for (size_t i=0; i<pattern.size(); i++) {
        std::cout << pattern[i] << "=" << result[i] << std::endl;
    }

    return 0;
}
}
