/*
 * Dummy.h
 *
 *  Created on: Apr 25, 2018
 *      Author: nazgee
 */

#ifndef SAMPLES_DUMMY_H_
#define SAMPLES_DUMMY_H_

#include "../Tutorials.h"

class Dummy : public ITutorial {
public:
    Dummy();
    ~Dummy();
    virtual void run(int argc, char** argv) override;
};

#endif /* SAMPLES_DUMMY_H_ */
