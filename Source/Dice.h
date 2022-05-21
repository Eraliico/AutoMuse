#pragma once

#include <random>

template <template<typename> class distType, typename T>
class Die{
	public:
		//Modifying
		Die(const T lower, const T upper):
			dist(lower, upper){}
		void Modify(const T lower, const T upper){
			dist = distType<T>{lower, upper};
		}

		//Const Operators
		static T Roll(const T lower, const T upper){
			return distType<T>{lower, upper}(rng);
		}
		T operator()() const{
			return dist(rng);
		}

		//Getters
		T Min() const{
			return dist.min();
		}
		T Max() const{
			return dist.max();
		}

	private:
		mutable distType<T> dist;
		static inline std::mt19937 rng{std::random_device{}()};
};

typedef Die<std::uniform_int_distribution, int> DiscreteDie;
typedef Die<std::uniform_real_distribution, float> RealDie;
