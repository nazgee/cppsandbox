/*
 * Thread1.cpp
 *
 *  Created on: Apr 25, 2018
 *      Author: nazgee
 */

#include <functional>
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

#include "Thread1.h"

#define LOOPS 10
#define SLEEPMS 100

namespace thread1 {

// thread object
class ThreadObject {
public:
    void operator()() {
        for(int i = 0; i < LOOPS; i++) {
            std::cout << "Object executing" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(SLEEPMS));
        }
    }
};

// thread function
void thread_function() {
    for(int i = 0; i < LOOPS; i++) {
        std::cout<<"Function executing"<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEPMS));
    }
}

// lambda
auto thread_lambda = []() {
    for(int i = 0; i < LOOPS; i++) {
        std::cout<<"Lambda executing"<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEPMS));
    }
};

int main(int argc, char** argv) {
    std::cout << "running " << __PRETTY_FUNCTION__ << std::endl;

    std::thread t1(thread_function);
    // XXX fails with "undefined reference to `thread1::tobj()'"
//    ThreadObject tobj();
//    std::thread t2((tobj));
    // XXX fails to create proper thread -- nothing starts
//    std::thread t2(ThreadObject());
    std::thread t2((ThreadObject()));
    std::thread t3(thread_lambda);

    // local threads will be moved to the vector
    std::vector<std::thread> v;

    v.push_back(std::move(t1));
    v.push_back(std::move(t2));
    v.push_back(std::move(t3));

    // XXX wait for all threads to complete
    std::for_each(v.begin(), v.end(), std::mem_fn(&std::thread::join));

    {
        int local1 = 1;
        // = 1
        std::cout << "local1=" << local1 << std::endl;

        auto lambda_ref = [&local1]() {
            local1++;
            std::cout << "ref local1=" << local1 << std::endl;
        };

        // this WILL change the value of local1
        // = 2
        lambda_ref();
        // = 3
        lambda_ref();
        // = 3
        std::cout << "REF local1=" << local1 << std::endl;

        // when lambdas capturing locals 'by value' are created, they keep their own copy
        auto lambda_val = [local1]() mutable {
            local1++;
            std::cout << "loc local1=" << local1 << std::endl;
        };

        // = 4
        lambda_val();
        // = 5
        lambda_val();
        // = 3
        std::cout << "LOC local1=" << local1 << std::endl;

        // = 4
        lambda_ref();
        // = 5
        lambda_ref();
        // = 5
        std::cout << "REF local1=" << local1 << std::endl;
    }

    return EXIT_SUCCESS;
}

}
