#ifndef TIME_PROFILER
#define TIME_PROFILER

#include <chrono>
#include <string>
#include <iostream>

class TimeProfiler
{
public:
    static void begin() {
        m_begin = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        );
    }

    static unsigned int end(std::string&& name, bool display = true) {
        m_end = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        );

        unsigned int time = m_end.count() - m_begin.count();
        if (display)
            std::cout << "-[" + name + "]: " << time << " ms" << std::endl;
        return time;
    }

private:
    static std::chrono::milliseconds m_begin;
    static std::chrono::milliseconds m_end;
};

#endif //TIME_PROFILER