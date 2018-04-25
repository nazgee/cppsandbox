/*
 * Base.cpp
 *
 *  Created on: Apr 25, 2018
 *      Author: nazgee
 */

#include "Base.h"

Base::Base(main_function f, std::string&& name) :
        ITutorial(std::move(name)), mFunction(f) {
}

Base::~Base() {
}

void Base::run(int argc, char** argv) {
    mFunction(argc, argv);
}
