#pragma once

#include <string>
#include "Concepts.h"
#include "Die.h"
#include <cassert>

class Composer{
	public:
		//Pipeline Entrypoint (Partitioner)
		void Compose() const;

	private:
		//Pipeline Functions
		void HarmonicGenerator(std::vector<Concepts::Section> composition) const; 

		//Technical Configuration
		std::string midipath;

		//Musical Configuration
		float duration = 16.0f;
		unsigned int maxSections = 4;

		//Dice
		Die<int> iDie;
		Die<float> fDie;
};
