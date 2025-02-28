#include "Timer.h"

#include <chrono>



namespace Engine
{
    static SizeType CurrentSystemTime()
    {
        using Clock = std::chrono::high_resolution_clock;
        using Unit  = std::chrono::milliseconds;


        auto duration = Clock::now().time_since_epoch();

        return std::chrono::duration_cast<Unit>(duration).count();
    }


    Timer::Timer()
    {
        Reset();
    }

    Void Timer::Reset()
    {
        start = CurrentSystemTime();
    }

    RealType Timer::Elapsed() const
    {
        return static_cast<RealType>( ElapsedMilliseconds() ) / 1000;
    }

    SizeType Timer::ElapsedMilliseconds() const
    {
        return CurrentSystemTime() - start;
    }
}