#include <iostream>
#include <memory>

#include "Config.h"
#include "Tutorials.h"

#include "samples/Dummy.h"
#include "samples/Base.h"
#include "samples/Thread1.h"
#include "samples/Darbud.h"
#include "samples/Caesar.h"
#include "samples/Prime.h"
#include "samples/Perfect.h"

std::shared_ptr<Config> cfg;

int main(int argc, char** argv) {
    cfg = std::make_shared<Config>(argc, argv);
    std::cout << cfg->toString() << std::endl;

    Tutorials::get().add(new Dummy());
    Tutorials::get().add(new Base(thread1::main, "thread1"));
    Tutorials::get().add(new Base(Darbud::main, "darbud"));
    Tutorials::get().add(new Base(Iwanodar::main, "iwanodar"));
    Tutorials::get().add(new Base(Caesar::main, "caesar"));
    Tutorials::get().add(new Base(Prime::main, "prime"));
    Tutorials::get().add(new Base(Perfect::main, "perfect"));

    Tutorials::get().run(cfg->getTutorial());
    std::cout << "BYE!" << std::endl;

    return EXIT_SUCCESS;
}
