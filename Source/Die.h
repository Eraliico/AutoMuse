#pragma once

#include <random>

template <typename T>
class Die{
	public:
		T operator()(const T lower, const T upper) const{
			return (T)std::uniform_real_distribution<float>{(float)lower, (float)upper}(rng);
		};

	private:
		const std::mt19937 rng{std::random_device{}()};
};
