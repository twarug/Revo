#pragma once

// Revo
#include <Revo/Config.hpp>

// C++
#include <chrono>

namespace rv
{
    using Clock_t     = std::chrono::steady_clock;
    using Duration_t  = Clock_t::duration;
    using TimePoint_t = Clock_t::time_point;
    using Period_t    = Clock_t::period;

    /// Simple pausable Clock class
    class Clock
    {
    public:

        /// Returns current time point
        static TimePoint_t Now();

        /// Creates clock with current time point
        Clock();

        /// Creates clock with given time point
        Clock(const TimePoint_t& timePoint);

        /// Defaulted copy-ctor
        Clock(const Clock&) = default;

        /// Defaulted copy-assign-op
        Clock& operator = (const Clock&) = default;

        /// Creates clock from rhs and then restarts rhs
        Clock(Clock&& rhs);

        /// Assigns clock from rhs and then restarts rhs
        Clock& operator = (Clock&& rhs);

        /// Defaulted dtor
        ~Clock() = default;

        /// Returns elapsed duration since creation/restart
        Duration_t GetElapsedDuration() const;

        /// Starts clock
        void Start();

        /// Pauses clock
        void Pause();

        /// Toggles clock between running and paused state
        void Toggle();

        /// Restarts clock to the current time point and return old one
        Duration_t Restart();

        /// Advances clock by given duration
        void Advance(const Duration_t& duration, bool advanceBackwards = false);

        /// Checks whether clock is running
        bool IsRunning() const;

        /// Checks whether clock is paused
        bool IsPaused() const;

        /// Checks whether given duration has passed since creation/restart
        bool HasPassed(const Duration_t& duration) const;

        /// Checks whether given duration has passed since creation/restart, if so - restarts clock
        bool CheckStep(const Duration_t& duration);

        /// Checks whether given duration has passed since creation/restart, if so - advances clock backwards by given duration
        bool CheckFixedStep(const Duration_t& duration);

        /// Invokes CheckFixedStep() while it is possible and returns the amount of invokes
        size_t CheckContinuousStep(const Duration_t& duration);

    private:

        TimePoint_t m_refPoint;
        TimePoint_t m_pausePoint;
    };

    /// Returns duration of any type casted to the default one
    template <typename Rep, typename Period>
    Duration_t AsDefaultDuration(const std::chrono::duration<Rep, Period>& duration)
    {
        return std::chrono::duration_cast<Duration_t>(duration);
    }

    /// Returns duration represented as nanoseconds
    template <typename Rep, typename Period>
    auto AsNanoseconds(const std::chrono::duration<Rep, Period>& duration)
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    }

    /// Returns duration represented as microseconds
    template <typename Rep, typename Period>
    auto AsMicroseconds(const std::chrono::duration<Rep, Period>& duration)
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    }

    /// Returns duration represented as milliseconds
    template <typename Rep, typename Period>
    auto AsMilliseconds(const std::chrono::duration<Rep, Period>& duration)
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }

    /// Returns duration represented as seconds
    template <typename Rep, typename Period>
    auto AsSeconds(const std::chrono::duration<Rep, Period>& duration)
    {
        return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    }

    /// Returns duration represented as seconds as float
    template <typename Rep, typename Period>
    auto AsFSeconds(const std::chrono::duration<Rep, Period>& duration)
    {
        return std::chrono::duration_cast<std::chrono::duration<float>>(duration).count();
    }

    /// Returns duration represented as seconds as double
    template <typename Rep, typename Period>
    auto AsDSeconds(const std::chrono::duration<Rep, Period>& duration)
    {
        return std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
    }
}
