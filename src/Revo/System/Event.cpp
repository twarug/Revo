#include <Revo/System/Event.hpp>

namespace rv
{
    Event::Event(EventType type)
        : m_type { type }
    {

    }

    EventType Event::GetType() const
    {
        return m_type;
    }
}
