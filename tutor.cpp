#include <iostream>
#include <memory>

#include "Config.h"
#include "Tutorials.h"

#include "samples/Dummy.h"

std::shared_ptr<Config> cfg;

int main(int argc, char** argv) {
	cfg = std::make_shared<Config>(argc, argv);
	std::cout << cfg->toString() << std::endl;
	
	Tutorials::get().add(new Dummy());

	Tutorials::get().run(cfg->getTutorial());
	std::cout << "BYE!" << std::endl;

	return EXIT_SUCCESS;
}
