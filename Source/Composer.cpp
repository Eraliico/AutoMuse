#include "Composer.h"

void Composer::Compose(const std::string& filepath) const{
	//Partitioner
	
}
void Composer::LoadRuleset(const std::string& filepath){
	//Opens and Validates File
	std::ifstream ruleset{filepath};
	ruleset ? 0 : throw std::invalid_argument{filepath + " could not be opened!"};

	//Loads Configuartion Variables
	{
		std::string varLine;
		for(std::getline(ruleset, varLine); !varLine.empty(); std::getline(ruleset, varLine)){
			//Extract Line Contents
			const auto firstSpace = varLine.find_first_of(' ');

			configuration[varLine.substr(0, firstSpace)] = firstSpace != varLine.npos ? varLine.substr(firstSpace + 1) : "";
		}
	}

	//THE REST
}
void Composer::Configure(const std::string& setting, const std::string& value){
	auto settingInConfig = configuration.find(setting);
	if(settingInConfig != configuration.end()){
		settingInConfig->second = value;
	}else{
		throw std::invalid_argument{setting + " was not found!"};
	}
}
