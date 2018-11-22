#include <Revo/System/Clock.hpp>

namespace rv
{
    TimePoint_t Clock::Now()
    {
        return Clock_t::now();
    }

    Clock::Clock()
        : m_refPoint { Now() }
        , m_pausePoint { Now() }
    {

    }

    Clock::Clock(const TimePoint_t& timePoint)
        : m_refPoint { timePoint }
        , m_pausePoint { timePoint }
    {

    }

    Clock::Clock(Clock&& rhs)
        : m_refPoint { rhs.m_refPoint }
        , m_pausePoint { rhs.m_pausePoint }
    {
        rhs.Restart();
    }

    Clock& Clock::operator = (Clock&& rhs)
    {
        if (this != &rhs)
        {
            m_refPoint = rhs.m_refPoint;
            m_pausePoint = rhs.m_pausePoint;

            rhs.Restart();
        }

        return *this;
    }

    Duration_t Clock::GetElapsedDuration() const
    {
        return IsPaused() ? m_pausePoint - m_refPoint : Now() - m_refPoint;
    }

    void Clock::Start()
    {
        m_refPoint += Now() - m_pausePoint;

        m_pausePoint = TimePoint_t{ Duration_t::zero() };
    }

    void Clock::Pause()
    {
        m_pausePoint = Now();
    }

    void Clock::Toggle()
    {
        if (IsPaused())
        {
            Start();
        }
        else
        {
            Pause();
        }
    }

    Duration_t Clock::Restart()
    {
        const Duration_t ret = GetElapsedDuration();

        m_pausePoint = TimePoint_t{ Duration_t::zero() };

        m_refPoint = Now();

        return ret;
    }

    void Clock::Advance(const Duration_t& duration, bool advanceBackwards)
    {
        if (advanceBackwards)
        {
            m_refPoint += duration;
        }
        else
        {
            m_refPoint -= duration;
        }
    }

    bool Clock::IsRunning() const
    {
        return m_pausePoint.time_since_epoch() == Duration_t::zero();
    }

    bool Clock::IsPaused() const
    {
        return m_pausePoint.time_since_epoch() != Duration_t::zero();
    }

    bool Clock::HasPassed(const Duration_t& duration) const
    {
        return duration <= GetElapsedDuration();
    }

    bool Clock::CheckStep(const Duration_t& duration)
    {
        if (HasPassed(duration))
        {
            Restart();

            return true;
        }
        else
        {
            return false;
        }
    }

    bool Clock::CheckFixedStep(const Duration_t& duration)
    {
        if (HasPassed(duration))
        {
            Advance(duration, true);

            return true;
        }
        else
        {
            return false;
        }
    }

    size_t Clock::CheckContinuousStep(const Duration_t& duration)
    {
        size_t count = 0;

        // TODO change loop into computation
        while (CheckFixedStep(duration))
        {
            ++count;
        }

        return count;
    }
}
