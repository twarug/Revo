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

        /// Return current time point
        static TimePoint_t Now();

        /// Create clock with current time point
        Clock();

        /// Create clock with given time point
        Clock(const TimePoint_t& timePoint);

        /// Defaulted copy-ctor
        Clock(const Clock&) = default;

        /// Defaulted copy-assign-op
        Clock& operator = (const Clock&) = default;

        /// Create clock from rhs and then restart rhs
        Clock(Clock&& rhs);

        /// Assign clock from rhs and then restart rhs
        Clock& operator = (Clock&& rhs);

        /// Defaulted dtor
        ~Clock() = default;

        /// Return elapsed duration since creation/restart
        Duration_t GetElapsedDuration() const;

        /// Start clock
        void Start();

        /// Pause clock
        void Pause();

        /// Toggle clock between running and paused state
        void Toggle();

        /// Restart clock to the current time point and return old one
        Duration_t Restart();

        /// Advance clock by given duration
        void Advance(const Duration_t& duration, bool advanceBackwards = false);

        /// Check whether clock is running
        bool IsRunning() const;

        /// Check whether clock is paused
        bool IsPaused() const;

        /// Check whether given duration has passed since creation/restart
        bool HasPassed(const Duration_t& duration) const;

        /// Check whether given duration has passed since creation/restart, if so - restart clock
        bool CheckStep(const Duration_t& duration);

        /// Check whether given duration has passed since creation/restart, if so - advances clock backwards by given duration
        bool CheckFixedStep(const Duration_t& duration);

        /// Invoke CheckFixedStep() while it is possible and return the amount of invokes
        size_t CheckContinuousStep(const Duration_t& duration);

    private:

        TimePoint_t m_refPoint;
        TimePoint_t m_pausePoint;
    };

    /// Return duration of any type casted to the default one
    template <typename Rep, typename Period>
    Duration_t AsDefaultDuration(const std::chrono::duration<Rep, Period>& duration)
    {
        return std::chrono::duration_cast<Duration_t>(duration);
    }

    /// Return duration represented as nanoseconds
    template <typename Rep, typename Period>
    auto AsNanoseconds(const std::chrono::duration<Rep, Period>& duration)
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    }

    /// Return duration represented as microseconds
    template <typename Rep, typename Period>
    auto AsMicroseconds(const std::chrono::duration<Rep, Period>& duration)
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    }

    /// Return duration represented as milliseconds
    template <typename Rep, typename Period>
    auto AsMilliseconds(const std::chrono::duration<Rep, Period>& duration)
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }

    /// Return duration represented as seconds
    template <typename Rep, typename Period>
    auto AsSeconds(const std::chrono::duration<Rep, Period>& duration)
    {
        return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    }

    /// Return duration represented as seconds as float
    template <typename Rep, typename Period>
    auto AsFSeconds(const std::chrono::duration<Rep, Period>& duration)
    {
        return std::chrono::duration_cast<std::chrono::duration<float>>(duration).count();
    }

    /// Return duration represented as seconds as double
    template <typename Rep, typename Period>
    auto AsDSeconds(const std::chrono::duration<Rep, Period>& duration)
    {
        return std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
    }

}
