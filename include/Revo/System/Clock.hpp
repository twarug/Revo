#pragma once

// Revo
#include <Revo/Config.hpp>

// C++
#include <chrono>

namespace rv
{
    using SteadyClock_t = std::chrono::steady_clock;
    using SystemClock_t = std::chrono::system_clock;
    using Duration_t    = SteadyClock_t::duration;
    using TimePoint_t   = SteadyClock_t::time_point;
    using Period_t      = SteadyClock_t::period;

    /// Simple pausable Clock class
    class Clock
    {
    public:

        /// Returns current time point
        static TimePoint_t Now();

        /// Creates clock with current time point
        Clock();

        /// Creates clock with given time point
        Clock(TimePoint_t const& timePoint);

        /// Defaulted copy-ctor
        Clock(Clock const&) = default;

        /// Defaulted copy-assign-op
        Clock& operator = (Clock const&) = default;

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
        void Advance(Duration_t const& duration, bool advanceBackwards = false);

        /// Checks whether clock is running
        bool IsRunning() const;

        /// Checks whether clock is paused
        bool IsPaused() const;

        /// Checks whether given duration has passed since creation/restart
        bool HasPassed(Duration_t const& duration) const;

        /// Checks whether given duration has passed since creation/restart, if so - restarts clock
        bool CheckStep(Duration_t const& duration);

        /// Checks whether given duration has passed since creation/restart, if so - advances clock backwards by given duration
        bool CheckFixedStep(Duration_t const& duration);

        /// Invokes CheckFixedStep() while it is possible and returns the amount of invokes
        size_t CheckContinuousStep(Duration_t const& duration);

    private:

        TimePoint_t m_refPoint;
        TimePoint_t m_pausePoint;
    };

    /// Returns duration of any type casted to the default one
    template <typename Rep, typename Period>
    constexpr Duration_t AsDefaultDuration(std::chrono::duration<Rep, Period> const& duration)
    {
        return std::chrono::duration_cast<Duration_t>(duration);
    }

    /// Returns duration represented as nanoseconds
    template <typename Rep, typename Period>
    constexpr auto AsNanoseconds(std::chrono::duration<Rep, Period> const& duration)
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    }

    /// Returns duration represented as microseconds
    template <typename Rep, typename Period>
    constexpr auto AsMicroseconds(std::chrono::duration<Rep, Period> const& duration)
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    }

    /// Returns duration represented as milliseconds
    template <typename Rep, typename Period>
    constexpr auto AsMilliseconds(std::chrono::duration<Rep, Period> const& duration)
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }

    /// Returns duration represented as seconds
    template <typename Rep, typename Period>
    constexpr auto AsSeconds(std::chrono::duration<Rep, Period> const& duration)
    {
        return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    }

    /// Returns duration represented as seconds as float
    template <typename Rep, typename Period>
    constexpr auto AsFSeconds(std::chrono::duration<Rep, Period> const& duration)
    {
        return std::chrono::duration_cast<std::chrono::duration<float>>(duration).count();
    }

    /// Returns duration represented as seconds as double
    template <typename Rep, typename Period>
    constexpr auto AsDSeconds(std::chrono::duration<Rep, Period> const& duration)
    {
        return std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
    }

    ///
    char const* GetReadableTime(Duration_t const& duration);
}
