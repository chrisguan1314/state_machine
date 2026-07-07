#include "timestamp.h"

Timestamp Timestamp::Now()
{
    return Now(TimeUnit::Microsecond);
}

Timestamp Timestamp::Now(TimeUnit unit)
{
    using namespace std::chrono;
    auto now = system_clock::now();
    auto micro = duration_cast<microseconds>(now.time_since_epoch()).count();
    Timestamp ts(micro);
    return ts;
}

int64_t Timestamp::ToValue(TimeUnit unit) const
{
    switch (unit)
    {
        case TimeUnit::Second:
            return m_microSec / kMicroSecPerSec;
        case TimeUnit::Millisecond:
            return m_microSec / kMilliPerSec;
        case TimeUnit::Microsecond:
            return m_microSec;
        case TimeUnit::Nanosecond:
            return m_microSec * 1000;
        default:
            return m_microSec;
    }
}

time_t Timestamp::ToTimeT() const
{
    return static_cast<time_t>(m_microSec / kMicroSecPerSec);
}

std::string Timestamp::ToString(const std::string& fmt) const
{
    time_t sec = ToTimeT();
    tm localTm{};

#ifdef _WIN32
    localtime_s(&localTm, &sec);
#elif __linux__
    localtime_r(&sec, &localTm);
#else
    localTm = *localtime(&sec);
#endif

    std::ostringstream oss;
    oss << std::put_time(&localTm, fmt.c_str());

    // 拼接毫秒
    if (fmt.find("%f") != std::string::npos)
    {
        int64_t ms = (m_microSec % kMicroSecPerSec) / kMilliPerSec;
        oss << std::setfill('0') << std::setw(3) << ms;
    }
    return oss.str();
}

std::string Timestamp::ToDateString() const
{
    return ToString("%Y-%m-%d");
}

std::string Timestamp::ToTimeString() const
{
    return ToString("%H:%M:%S");
}

bool Timestamp::operator<(const Timestamp& other) const
{
    return m_microSec < other.m_microSec;
}

bool Timestamp::operator>(const Timestamp& other) const
{
    return m_microSec > other.m_microSec;
}

bool Timestamp::operator==(const Timestamp& other) const
{
    return m_microSec == other.m_microSec;
}

bool Timestamp::operator!=(const Timestamp& other) const
{
    return !(*this == other);
}

Timestamp Timestamp::operator+(int64_t microSec) const
{
    return Timestamp(m_microSec + microSec);
}

Timestamp Timestamp::operator-(int64_t microSec) const
{
    return Timestamp(m_microSec - microSec);
}

int64_t Timestamp::DiffMicroSec(const Timestamp& other) const
{
    return m_microSec - other.m_microSec;
}

void Timestamp::Sleep(int64_t val, TimeUnit unit)
{
    int64_t ms = 0;
    switch (unit)
    {
        case TimeUnit::Second:
            ms = val * 1000; break;
        case TimeUnit::Millisecond:
            ms = val; break;
        case TimeUnit::Microsecond:
            ms = val / 1000; break;
        case TimeUnit::Nanosecond:
            ms = val / 1000000; break;
    }

#ifdef _WIN32
    ::Sleep(static_cast<DWORD>(ms));
#elif __linux__ || __unix__
    usleep(static_cast<useconds_t>(ms * 1000));
#endif
}