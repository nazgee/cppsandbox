/*
 * Config.h
 *
 *  Created on: Apr 25, 2018
 *      Author: nazgee
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <memory>

class Config {
    int mSilent = 0;
    std::string mTutorial;

public:
    Config(int argc, char **argv);
    ~Config();

    std::string getTutorial() {
        return mTutorial;
    }

    bool isVerbose() {
        return mSilent;
    }

    std::string toString();
};

// XXX this is silly way to share config - done on purpose
extern std::shared_ptr<Config> cfg;

#endif /* CONFIG_H_ */
