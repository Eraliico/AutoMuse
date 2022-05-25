#include "Composer.h"

Composer::Composer(const Concepts::Key& keyRef):
	key(keyRef){}

void Composer::Compose() const{
	//Partitioner
	//Roll for # of sections
	const int nSections = sectionsDie();
	const int unique = sectionsDie.Roll(1, nSections);

	//Compute percentages per unique ID
	float percentsPerID[unique];
	{
		for(int id = 0; id < unique; ++id){
			percentsPerID[id] = 0.0f;
		}
		
		float totalPercentage = 0.0f;
		while(totalPercentage < 1.0f){
			for(int i = 0; i < unique; ++i){
				const float growth = growthDie();
				percentsPerID[i] += growth;
				totalPercentage += growth;
			}
		}
		percentsPerID[unique - 1] -= totalPercentage - 1.0f;
	}

	//Assign duplicate sections
	int duplicatesPerID[unique];
	{
		for(int id = 0; id < unique; ++id){
			duplicatesPerID[id] = 0;
		}

		const int remainder = nSections - unique;
		for(int i = 0; i < remainder; ++i){
			++duplicatesPerID[sectionsDie.Roll(0, unique - 1)];
		}
	}


	//Construct sections
	Concepts::Composition composition;
	composition.track.reserve(nSections);
	for(unsigned int id = 0; id < unique; ++id){
		for(unsigned int d = 0; d <= duplicatesPerID[id]; ++d){
			composition.track.emplace_back(id, percentsPerID[id] / (duplicatesPerID[id] + 1.0f) * duration);
		}
	}
	std::shuffle(composition.track.begin(), composition.track.end(), std::mt19937(std::random_device{}()));
	composition.idCount = unique;

	//Pass to harmonic generator
	HarmonicGenerator(composition);

}
void Composer::HarmonicGenerator(Concepts::Composition& composition) const{
	bool generated[composition.idCount];
	for(auto& section : composition.track){
		if(!generated[section.identifier]){
			//Make a new chord progression using degrees
			const unsigned int nChords = int(averageChordDensity * section.duration);
			assert(nChords > 0);
			unsigned int progDegrees[nChords];
			progDegrees[nChords - 1] = 0;
			progDegrees[0] = degreeDie();
			for(int c = 1; c < nChords - 1; ++c){
				auto deg = degreeDie();
				while(deg == progDegrees[c - 1]){
					deg = degreeDie();
				}
				progDegrees[c] = deg;
			}
			
			//Translate degrees and insert as domains
			section.track.reserve(nChords);
			for(int c = 0; c < nChords; ++c){
				section.track.emplace_back(Concepts::ChordAt(key, progDegrees[c]));
			}

			generated[section.identifier] = true;
		}else{
			//Copy from existing prog
			const auto& source = std::find_if(composition.track.begin(), composition.track.end(), [&section](const auto& s){
				return s.identifier == section.identifier;
			});
			assert(!source->track.empty());

			section.track = source->track;
		}
	}

	DEBUG_EndOfPipeline(composition);
}

void Composer::DEBUG_EndOfPipeline(Concepts::Composition& composition) const{
	std::string toneNames[12] = {
		"A", "Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab"
	};
	std::string qualNames[3] = {
		"", "m", "0"
	};
	std::string modeNames[7] = {
		"Minor",
		"Locrian",
		"Major",
		"Dorian",
		"Phrygian",
		"Lydian",
		"Mixolydian"
	};

	std::cout << "Total Duration: " << duration << " measures\n";
	std::cout << "Key: " << toneNames[(size_t)key.first] << ' ' << modeNames[(size_t)key.second] << std::endl;
	std::cout << "Sections Generated: " << composition.track.size() << std::endl;
	std::cout << "Unique Section IDs: " << composition.idCount << std::endl;
	for(int s = 0; s < composition.track.size(); ++s){
		std::cout << "=== SECTION " << s << ", ID " << composition.track[s].identifier << ", " << composition.track[s].duration << " MEASURES ===\n";
		for(const auto& domain : composition.track[s].track){
			std::cout << '\t' << toneNames[(size_t)domain.chord.first] << qualNames[(size_t)domain.chord.second] << std::endl;
		}
	}
}
