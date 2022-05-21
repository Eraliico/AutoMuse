#pragma once

#include <vector>

namespace Concepts{
	enum Tone{
		A = 0,
		B = 2,
		C = 3,
		D = 5,
		E = 7,
		F = 8,
		G = 10
	};
	enum Quality{
		Major,
		Minor,
		Diminished,
		Augmented,
		Major6,
		Minor6,
		Seventh,
		Major7,
		Minor7,
		Diminished7
	};
	enum Fashion{
		Block,
		Arpeggiative,
		Intermittent
	};

	struct Note{
		float position;
		float duration;

		Tone tone;
		int sharpness;
		int octave;
		//ornaments... to be implemented
	
	};
	
	template <typename Subordinate>
	struct Partition{
		std::vector<Subordinate> track;
	};
	struct Subdomain : public Partition<Note>{
		bool isMotte;
	};
	struct Domain : public Partition<Subdomain>{
		Tone tone;
		Quality quality;
		Fashion fashion;
		bool hasTransition;
	};
	struct Section : public Partition<Domain>{
		unsigned int identifier;
		float duration;
	};
}
