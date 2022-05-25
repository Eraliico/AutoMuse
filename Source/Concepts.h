#pragma once

#include <vector>

namespace Concepts{
	enum class Tone{
		A, Bb, B, C, Db, D, Eb, E, F, Gb, G, Ab
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
	typedef std::pair<Tone, Quality> Chord;
	enum class Fashion{
		Block,
		Arpeggiative,
		Intermittent
	};
	enum class Mode{
		Minor,
		Locrian,
		Major,
		Dorian,
		Phrygian,
		Lydian,
		Mixolydian
	};
	typedef std::pair<Tone, Mode> Key;
	static int Intervals[7] = {0, 2, 3, 5, 7, 8, 10};
	static Quality Triads[7] = {
		Quality::Minor,
		Quality::Diminished,
		Quality::Major,
		Quality::Minor,
		Quality::Minor,
		Quality::Major,
		Quality::Major
	};

	static Tone Transpose(const Tone& tone, const int interval){
		return Tone((((int)tone + interval) % 12 + 12) % 12);
	}
	static Tone ToneAt(const Key& key, const unsigned int degree){
		return Transpose(Tone(Intervals[((unsigned int)key.second + degree) % 7]), (int)key.first - Intervals[(size_t)key.second]);
	}
	static Chord ChordAt(const Key& key, const unsigned int degree){
		return {ToneAt(key, degree), Triads[(degree + (unsigned int)key.second) % 7]};
	}

	struct Note{
		float position;
		float duration;

		Tone tone;
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
		Domain(const Chord& chordRef):
			chord(chordRef){}

		Chord chord;
		Fashion fashion = Fashion::Block;
		bool hasTransition = false;
	};
	struct Section : public Partition<Domain>{
		Section(const unsigned int id, const float dur):
			identifier(id),
			duration(dur){}

		unsigned int identifier;
		float duration;
	};
	struct Composition : public Partition<Section>{
		unsigned int idCount;
	};
}
