/*
 * Caesar.cpp
 *
 *  Created on: Apr 25, 2018
 *      Author: nazgee
 */

#include <functional>
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <string>
#include <assert.h>
#include <algorithm>
#include <cmath>

#include "Caesar.h"

namespace Caesar {

static auto shiftby = [](int c, int n) -> char {
    const int letters = 'z' - 'a' + 1;

    n = (n % letters + letters) % letters;
    if (::islower(c)) {
        c -= 'a';
        c = (c + n) % letters;
        return c + 'a';
    } else if (::isupper(c)) {
        c -= 'A';
        c = (c + n) % letters;
        return c + 'A';
    } else {
        return c;
    }
};

class CaesarCipher
{
public:
    static std::vector<std::string> movingShift(const std::string &s, int shift) {
        // prepare the output (do the 'encoding')
        std::string output = s;
        std::transform(output.begin(), output.end(), output.begin(),
                [&shift](char c) -> char {
                    return shiftby(c, shift++);
                });

        // calculate the chunksize, and prepare the output vector
        size_t chunksize = std::ceil(s.length() / 5.0f);
        std::vector<std::string> chunks(5);

        // split the output to chunks
        size_t beg = 0;
        for (std::string& s : chunks) {
            size_t offset = std::min(chunksize, output.size() - beg);
            s = output.substr(beg, offset);
            beg += offset;
        }

        return chunks;
    }

    static std::string demovingShift(std::vector<std::string> &s, int shift) {
        // merge all chunks
        std::string output;
        for (std::string& chunk : s) {
            output += chunk;
        }

        // prepare the output (do the 'decoding')
        std::transform(output.begin(), output.end(), output.begin(),
                [&shift](char c) -> char {
                    return shiftby(c, -shift++);
                });

        return output;
    }
};

//==============================================================================

void testequal1(std::vector<std::string> ans, std::vector<std::string> sol)
{
    std::cout << "=====" << std::endl;
    for (size_t i = 0; i < ans.size(); i++) {
        std::cout << "assert that '" << ans[i] << "' == '" << sol[i] << "'" << std::endl;
    }
    std::cout << "-----" << std::endl;
    assert(ans == sol);
}
static void dotest1(const std::string &s, int shift, std::vector<std::string> expected)
{
    testequal1(CaesarCipher::movingShift(s, shift), expected);
}

void testequal2(std::string ans, std::string sol)
{
    std::cout << "assert that '"<< ans << "' == '" << sol << "'" << std::endl;
    assert(ans == sol);
}
static void dotest2(std::vector<std::string> &s, int shift, std::string expected)
{
    testequal2(CaesarCipher::demovingShift(s, shift), expected);
}

void testequal3(std::string ans, std::string sol)
{
    std::cout << "assert that '"<< ans << "' ==' " << sol << "'" << std::endl;
    assert(ans == sol);
}
static void dotest3(std::string s, int shift)
{
    std::vector<std::string> r = CaesarCipher::movingShift(s, shift);
    testequal3(CaesarCipher::demovingShift(r, shift), s);
}

int main(int argc, char** argv) {
    std::cout << "running " << __PRETTY_FUNCTION__ << std::endl;

    std::string  u = "I should have known that you would have a perfect answer for me!!!";
    std::vector<std::string> sol = {"J vltasl rlhr ", "zdfog odxr ypw", " atasl rlhr p ", "gwkzzyq zntyhv", " lvz wp!!!"};
    dotest1(u, 1, sol);
    dotest2(sol, 1, u);
    dotest3(u, 1);

    u = "O CAPTAIN! my Captain! our fearful trip is done;";
    dotest3(u, 1);

    return EXIT_SUCCESS;
}

}
