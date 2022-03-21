#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include "Composer.h"

int main(){
	Composer bruh;
	bruh.LoadRuleset("example.txt");
	bruh.PrintConfig(std::cout);
}
