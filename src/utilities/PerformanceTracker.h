//
// Created by cmchan04 on 6/16/2025.
//

#pragma once
#include <iostream>
#include <chrono>

#define byte WindowsByte
#include <windows.h>
#include <psapi.h>
#undef byte


using namespace std;
using namespace std::chrono;

class PerformanceTracker {
private:
    high_resolution_clock::time_point startTime;
    high_resolution_clock::time_point endTime;
    SIZE_T peakMemoryUsage;

public:
    PerformanceTracker();

    void start();
    void stop();
    void updatePeakMemory();
    void report(const string& label = "Performance") const;

    SIZE_T getPeakMemoryBytes() const;
};

