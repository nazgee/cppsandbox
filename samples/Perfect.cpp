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

#include "Perfect.h"

namespace Perfect {

// function with lvalue and rvalue reference overloads:
void overloaded (int& x) {std::cout << "[lvalue] @" << &x;}
void overloaded (int&& x) {std::cout << "[rvalue] @" << &x;}

template<typename T>
void overload_wrapper_template(T&& arg) {
    arg += 2;

    auto showme = [](std::string s, bool show) {
        if (show)
            std::cout << s << std::endl;
    };

    showme("<int, T>", std::is_same<int, T>::value);
    showme("<int&, T>", std::is_same<int&, T>::value);
    showme("<int&&, T>", std::is_same<int&&, T>::value);

    showme("<int, decltype(arg)>", std::is_same<int, decltype(arg)>::value);
    showme("<int&, decltype(arg)>", std::is_same<int&, decltype(arg)>::value);
    showme("<int&&, decltype(arg)>", std::is_same<int&&, decltype(arg)>::value);

    T& argref = arg;
    showme("<int, decltype(argref)>", std::is_same<int, decltype(argref)>::value);
    showme("<int&, decltype(argref)>", std::is_same<int&, decltype(argref)>::value);
    showme("<int&&, decltype(argref)=", std::is_same<int&&, decltype(argref)>::value);

    std::cout << "---" << std::endl;

    std::cout << "always an lvalue ";
    overloaded(arg);                   // always an lvalue
    std::cout << std::endl;

    std::cout << "back to it's original nature, thanks to std::forward ";
    overloaded(std::forward<T>(arg));  // rvalue if argument is rvalue
    std::cout << std::endl;
}

void overload_wrapper_no_template(int&& arg) {
    std::cout << "arg @ " << &arg << std::endl;;

    // lvalue on reference to arg
    std::cout << "no template, just arg ";
    overloaded(arg);
    std::cout << std::endl;

    // rvalue on a NEW temporary object created
    std::cout << "no template, static_cast to int ";
    overloaded(static_cast<int>(arg));
    std::cout << std::endl;

    // lvalue on reference to arg (static_cast is pointless here)
    std::cout << "no template, static_cast to int& ";
    overloaded(static_cast<int&>(arg));
    std::cout << std::endl;

    // rvalue reference
    std::cout << "no template, static_cast to int&& ";
    overloaded(static_cast<int&&>(arg));
    std::cout << std::endl;

    // rvalue reference -- will NOT create new temporary object, nice!
    std::cout << "no template, forward to int ";
    overloaded(std::forward<int>(arg));
    std::cout << std::endl;

    // lvalue on reference to arg
    std::cout << "no template, forward to int& ";
    overloaded(std::forward<int&>(arg));
    std::cout << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "running " << __PRETTY_FUNCTION__ << std::endl;

    int a = 7;
    int& a_ref = a;

    std::cout << "=== template, force deduction to int&" << std::endl;
    overload_wrapper_template<int&>(a);
    std::cout << "=== template, auto deduction of lvalue reference" << std::endl;
    overload_wrapper_template(a_ref);
    std::cout << "=== template, auto deduction of lvalue" << std::endl;
    overload_wrapper_template(a);

    std::cout << "=== template, force deduction to int&&" << std::endl;
    overload_wrapper_template<int&&>(7);
    std::cout << "=== template, auto rvalue deduction of rvalue" << std::endl;
    overload_wrapper_template(7);

    std::cout << "=== no template, passing rvalue" << std::endl;
    overload_wrapper_no_template(0);
    // XXX this is why templates work nice with perfect forwarding...
//    overload_wrapper_no_template(a);

    return 0;
}

}
