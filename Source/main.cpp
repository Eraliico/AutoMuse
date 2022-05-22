#include <iostream>
#include "Composer.h"

Composer composer;

int main(){
	const auto test = composer.Compose();

	for(const auto& s : test){
		std::cout << s.identifier << ": " << s.duration << " measures\n";
	}

	return 0;
}
