#pragma once

#include <unordered_map>
#include <string>
#include <stdexcept>
#include <fstream>

class Composer{
	public:
		//Pipeline Entrypoint (Partitioner)
		void Compose(const std::string& filepath) const;

		void LoadRuleset(const std::string& filepath);
		void Configure(const std::string& setting, const std::string& value);

	private:
		//Compositional Configuration
		std::unordered_map<std::string, std::string> configuration{
			{"duration", "16"},
			{"quirk", "0"}
		};

		//Abstract Stage

};
