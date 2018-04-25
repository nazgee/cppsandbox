/*
 * Dummy.cpp
 *
 *  Created on: Apr 25, 2018
 *      Author: nazgee
 */

#include "Dummy.h"

Dummy::Dummy() : ITutorial(__FUNCTION__) {
}

Dummy::~Dummy() {
}

void Dummy::run(int argc, char** argv) {
    std::cout << "running " << __PRETTY_FUNCTION__ << std::endl;
}
