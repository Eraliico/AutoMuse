#pragma once

#include <vector>

namespace Concepts{
	enum class Tone{
		A = 0,
		B = 2,
		C = 3,
		D = 5,
		E = 7,
		F = 8,
		G = 10
	};
	enum class Quality{
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
	enum class Fashion{
		Block,
		Arpeggiative,
		Intermittent
	};
	enum class Mode{
		Major,
		Dorian,
		Phrygian,
		Lydian,
		Mixolydian,
		Minor,
		Locrian
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
		Section(const unsigned int id, const float dur):
			identifier(id),
			duration(dur){}
		unsigned int identifier;
		float duration;
	};
}
