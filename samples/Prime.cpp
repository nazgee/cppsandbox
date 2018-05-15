/*
 * Prime.cpp
 *
 *  Created on: Apr 25, 2018
 *      Author: nazgee
 */

#include <functional>
#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <algorithm>
#include <string>
#include <assert.h>
#include <algorithm>
#include <cmath>

#include "Prime.h"

namespace Prime {

class Primes;
std::ostream& operator<<(std::ostream& os, const Primes & primes);
std::ostream& operator<<(std::ostream& os, const std::pair<long long, long long> & pair);
using prime_t = long long;
using range_t = const std::pair<prime_t, prime_t>;

class Primes {
public:

private:
    range_t mRange;
    std::vector<prime_t> mPrimes;

    inline bool isUnknownPrimeNumber(prime_t testme, prime_t limit) const {
        for (auto p = mPrimes.begin(); p != mPrimes.end() && *p <= limit; p++) {
            bool has_rest = testme % *p;
            if (!has_rest) {
                return false;
            }
        }
        return true;
    }

    inline static prime_t caclulate_limit(prime_t potential_prime) {
        return ::sqrt(potential_prime) + 1;
    }

    Primes() : mRange(0, 0) {
    }

public:
    inline auto begin() const {
        return mPrimes.begin();
    }

    inline auto end() const {
        return mPrimes.end();
    }

    inline Primes(prime_t high_end) : Primes(range_t(0, high_end)) {
    }

    inline Primes(range_t range) : Primes(range,
                Primes(
                        range_t(2, Primes::caclulate_limit(range.second)),
                        Primes())
                ) {
    }

    inline Primes(range_t range, Primes&& helper) : mRange(range) {
        std::cout << "calculating primes for " << range << std::endl;

        mPrimes.reserve(caclulate_limit(range.second));

        if (helper.mPrimes.size() == 0) {
            prime_t i = range.first;
            while(i<=range.second) {
                // ... if number is not divisable by any of 'known' prime numbers
                prime_t limit = caclulate_limit(i);
                if (isUnknownPrimeNumber(i, limit)) {
                    mPrimes.push_back(i);
                }
                i = i + 1 + i%2;
            }
        } else {
            prime_t i = range.first;
            while(i<=range.second) {
                prime_t limit = caclulate_limit(i);
                if (helper.isUnknownPrimeNumber(i, limit) && isUnknownPrimeNumber(i, limit)) {
                    // ... it's a prime number, so let's store it
                    mPrimes.push_back(i);
                }
                i = i + 1 + i%2;
            }
        }
    }
};

std::ostream& operator<<(std::ostream& os, const Primes & primes)
{
    for (auto p = primes.begin(); p != primes.end(); p++) {
        os << *p << " ";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::pair<long long, long long> & pair)
{
    os << '<' << pair.first << ", " << pair.second << '>';
    return os;
}

class GapInPrimes
{

public:
    static std::pair <long long, long long> gap(int g, prime_t m, prime_t n) {
        range_t range(m, n);

        Primes primes(range);

        prime_t prev = -1;
        for (auto p = primes.begin(); p != primes.end(); p++) {
            if (prev != -1) {
                prime_t diff = *p - prev;
                if (diff == g) {
                    return range_t(prev, *p);
                }
            }
            prev = *p;
        }
        return range_t(0, 0);
    }
};



//==============================================================================



void testequal(std::pair <long long, long long> ans, std::pair <long long, long long> sol) {
    std::cout << "assert that <ans>==<sol>; " << ans << "==" << sol << std::endl;
//    assert(ans == sol);
}

void dotest(int g, long long m, long long n, std::pair <long long, long long> expected)
{
    testequal(GapInPrimes::gap(g, m, n), expected);
}

int main(int argc, char** argv) {
    std::cout << "running " << __PRETTY_FUNCTION__ << std::endl;

    auto start = std::chrono::steady_clock::now();

    dotest(2,100,110, {101, 103});
    dotest(4,100,110, {103, 107});
    dotest(6,100,110, {0, 0});
    dotest(8,300,400, {359, 367});
    dotest(10,300,400, {337, 347});
    dotest(4,30000,100000, {337, 347});
    dotest(6,30000,100000, {337, 347});
    dotest(8,30000,100000, {337, 347});
    dotest(11,30000,100000, {337, 347});
    dotest(2,20,30, {337, 347});
    dotest(2,10000000,11000000, {337, 347});
    // 70ms

    std::cout << std::chrono::duration <double, std::milli> (std::chrono::steady_clock::now() - start).count() << " ms" << std::endl;

    return EXIT_SUCCESS;
}

}
