/*
 * Tutorials.h
 *
 *  Created on: Apr 25, 2018
 *      Author: nazgee
 */

#ifndef TUTORIALS_H_
#define TUTORIALS_H_

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <algorithm> // for_each

class ITutorial {
    std::string mName;
public:
    // XXX using 'aliases' instead of typedefs
    using shared_ptr = std::shared_ptr<ITutorial>;
    // XXX this is 'old' way of defining types
    // typedef std::shared_ptr<ITutorial> shared_ptr_old;

    ITutorial(std::string&& name) :
            mName(name) {
    }

    virtual void run(int argc, char** argv) = 0;
    virtual std::string& getName() {
        return mName;
    }
    virtual ~ITutorial() {
    }
};

class Tutorials {
public:
    using pair_name_to_tutorial = std::pair<std::string, ITutorial::shared_ptr>;
private:
	std::map<std::string, ITutorial::shared_ptr> mTutorials;
    Tutorials();
public:
    // XXX singletons are evil, but... we can, this is just a tutorial
    static Tutorials& get() {
        // XXX: If control enters the declaration concurrently while the variable
        // is being initialized, the concurrent execution shall wait for
        // completion of the initialization (a.k.a. c++11 singletons need no locking)
        static Tutorials instance;
        return instance;
    }
	
	void add(ITutorial* tutorial) {
	    // XXX go through a range and modify it in external buffer
        std::string& name = tutorial->getName();
        std::string lowercase = name;
        std::transform(name.begin(), name.end(), lowercase.begin(), ::tolower);

        mTutorials[lowercase].reset(tutorial);
	}

    void run(std::string name) {
        // XXX this is a funny way to go through a range and modify it in-place
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);

        // TODO prepare arguments for ITutorials (stubbed versions for now)
        int argc = 0;
        char** argv = nullptr;

        // build lambda, that will run the test with some eye-candy
        auto runner = [](int argc, char** argv, pair_name_to_tutorial p) {
            std::cout << "+++++ running   '" << p.first << "'" << std::endl;
            p.second->run(argc, argv);
            std::cout << "----- completed '" << p.first << "'" << std::endl;
        };

        // XXX use bind, to always pass argc and argv, and leave one placeholder for pair
        auto bound_runner = std::bind(runner, argc, argv,
                std::placeholders::_1);

        // XXX this will obviously fail... with segfault caused by nullptr deref
//      bound_runner(std::pair<std::string, ITutorial::shared_ptr>("dupa", ITutorial::shared_ptr(nullptr)));

        if (name == "") {
            std::for_each(mTutorials.begin(), mTutorials.end(), bound_runner);
            // XXX this would also be c++11, but lambdas are trendy now...
//	        for(auto t : mTutorials) {
//	            t.second->run(argc, argv);
//	        }

        } else {
            auto tutorial = mTutorials.find(name);
            if (tutorial != mTutorials.end()) {
                bound_runner(*tutorial);
            } else {
                throw std::runtime_error("'" + name + "' tutorial not found");
            }
        }
    }

    ~Tutorials();
};

#endif /* TUTORIALS_H_ */
