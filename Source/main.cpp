#include "Dice.h"
#include <iostream>

int main(){
	DiscreteDie dd{0, 10};
	RealDie rd{0.0f, 10.0f};

	for(int i = 0; i < 10; ++i){
		std::cout << dd() << std::endl << rd() << std::endl;
	}

	return 0;
}
