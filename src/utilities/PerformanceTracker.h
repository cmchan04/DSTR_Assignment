//
// Created by cmchan04 on 6/16/2025.
//

#pragma once
#include <iostream>
#include <chrono>

#if defined(_WIN32) || defined(_WIN64)
    #define OS_WINDOWS
    #define byte WindowsByte
    #include <windows.h>
    #include <psapi.h>
    #undef byte
#elif defined(__APPLE__) || defined(__MACH__)
    #define OS_MAC
    #include <mach/mach.h>
#endif

using namespace std;
using namespace std::chrono;

class PerformanceTracker {
private:
    high_resolution_clock::time_point startTime;
    high_resolution_clock::time_point endTime;
    size_t peakMemoryUsage;

public:
    PerformanceTracker();

    void start();
    void stop();
    void updatePeakMemory();
    void report(const string& label = "Performance") const;

    size_t getPeakMemoryBytes() const;
};

