#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
public:
    std::chrono::high_resolution_clock::time_point m_last;
    std::chrono::duration<double> m_elapsed;

    inline std::chrono::high_resolution_clock::time_point now()
    {
        return std::chrono::high_resolution_clock::now();
    }
    inline void restart()
    {
        m_last = now();
    }

    inline void stop()
    {
        m_elapsed = now() - m_last;
    }
   
    template <typename T>
    inline std::chrono::duration<double> elapsed()
    {
        return std::chrono::duration_cast<T>(m_elapsed);
    }

    template <typename T>
    inline double count()
    {
        stop();
        auto el = elapsed<T>();
        return el.count();
    }
};

#endif // TIMER_H
