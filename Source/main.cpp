#include <iostream>
#include "Composer.h"
#include <string>

int main(int argc, char** argv){
	Composer composer{{(Concepts::Tone)std::stoi(std::string(argv[1])), (Concepts::Mode)std::stoi(std::string(argv[2]))}};
	composer.Compose();
	
	return 0;
}
