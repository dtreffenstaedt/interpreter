#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
private:
    std::chrono::high_resolution_clock::time_point m_last;
    std::chrono::duration<double> m_elapsed;

    inline std::chrono::high_resolution_clock::time_point now()
    {
        return std::chrono::high_resolution_clock::now();
    }

public:
    void restart()
    {
        m_last = now();
    }

    void stop()
    {
        m_elapsed = now() - m_last;
    }
   
    template <typename T>
    std::chrono::duration<double> elapsed()
    {
        return std::chrono::duration_cast<T>(m_elapsed);
    }
};

#endif // TIMER_H
