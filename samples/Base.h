/*
 * Base.h
 *
 *  Created on: Apr 25, 2018
 *      Author: nazgee
 */

#ifndef SAMPLES_Base_H_
#define SAMPLES_Base_H_

#include "../Tutorials.h"

class Base : public ITutorial {
public:
    using main_function = std::function<int(int argc, char** argv)>;
private:
    main_function mFunction;
public:
    Base(main_function f, std::string&& name);
    ~Base();
    virtual void run(int argc, char** argv) override;
};

#endif /* SAMPLES_Base_H_ */
