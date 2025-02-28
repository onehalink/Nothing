#include "RandomNumber.h"

#include <chrono>
#include <random>



namespace Engine::Private
{
	RealType RandomReal(RealType minimum, RealType maximum)
	{
		using RandomNumberGenerator	= std::mt19937_64;
		using Distribution			= std::uniform_real_distribution<RealType>;


		RandomNumberGenerator generator;
		generator.seed( std::chrono::high_resolution_clock::now().time_since_epoch().count() );

		return Distribution(minimum, maximum)(generator);
	}
}