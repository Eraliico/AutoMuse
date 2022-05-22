#include "Composer.h"

std::vector<Concepts::Section> Composer::Compose() const{
	//Partitioner
	//Roll for # of sections
	const int nSections = iDie.Roll(1, maxSections);
	const int unique = iDie.Roll(1, nSections);
	assert(unique <= nSections);

	//Compute percentages per unique ID
	float percentsPerID[unique];
	{
		for(int id = 0; id < unique; ++id){
			percentsPerID[id] = 0.0f;
		}
		
		float totalPercentage = 0.0f;
		while(totalPercentage < 1.0f){
			for(int i = 0; i < unique; ++i){
				const float growth = fDie.Roll(.01f, .05f);
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
			++duplicatesPerID[iDie.Roll(0, unique - 1)];
		}
	}


	//Construct sections
	std::vector<Concepts::Section> composition;
	composition.reserve(nSections);
	for(unsigned int id = 0; id < unique; ++id){
		for(unsigned int d = 0; d <= duplicatesPerID[id]; ++d){
			composition.emplace_back(id, percentsPerID[id] / (duplicatesPerID[id] + 1.0f) * duration);
		}
	}
	std::shuffle(composition.begin(), composition.end(), std::mt19937(std::random_device{}()));

	//Pass to harmonic generator
	return composition;

}
void Composer::HarmonicGenerator(std::vector<Concepts::Section> composition) const{
	
}
