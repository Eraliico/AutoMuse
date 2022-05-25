#pragma once

#include <string>
#include "Concepts.h"
#include "Dice.h"
#include <cassert>
#include <algorithm>
#include <iostream>
#include <string>

class Composer{
	public:
		//Constructor (FOR DEBUGGING)
		Composer() = default;
		Composer(const Concepts::Key& keyRef);

		//Pipeline Entrypoint (Partitioner)
		void Compose() const;

	private:
		//Pipeline Functions
		void HarmonicGenerator(Concepts::Composition& composition) const; 
		void DEBUG_EndOfPipeline(Concepts::Composition& composition) const;

		//Technical Configuration
		std::string midipath = "filler";

		//Musical Configuration
		float duration = 16.0f;
		unsigned int maxSections = 4;
		Concepts::Key key = {Concepts::Tone::A, Concepts::Mode::Minor};
		float averageChordDensity = 2.0f;

		//Dice
		DiscreteDie sectionsDie{1, (int)maxSections};
		RealDie growthDie{0.01f, 0.05f};
		DiscreteDie degreeDie{0, 6};
};
