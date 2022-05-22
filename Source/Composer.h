#pragma once

#include <string>
#include "Concepts.h"
#include "Dice.h"
#include <cassert>
#include <algorithm>

class Composer{
	public:
		//Pipeline Entrypoint (Partitioner)
		std::vector<Concepts::Section> Compose() const;

	private:
		//Pipeline Functions
		void HarmonicGenerator(std::vector<Concepts::Section> composition) const; 

		//Technical Configuration
		std::string midipath = "filler";

		//Musical Configuration
		float duration = 16.0f;
		unsigned int maxSections = 4;
		Concepts::Tone keyTone = Concepts::Tone::A;
		int keySharpness = 0;
		Concepts::Mode keyMode = Concepts::Mode::Major;

		//Dice
		DiscreteDie iDie{0, 1};
		RealDie fDie{0.0f, 1.0f};
};
