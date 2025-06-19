//
// Created by cmchan04 on 6/16/2025.
//

// Imports and namespaces
#pragma once

#include <chrono>
#include <thread>
#include <atomic>

using namespace std;
using namespace std::chrono;

// Manage imports for different OS: This is for Windows computer
#if defined(_WIN32) || defined(_WIN64)
    #define OS_WINDOWS
    #define byte WindowsByte
    #include <windows.h>
    #include <psapi.h>
    #undef byte

// This is for Mac computers
#elif defined(__APPLE__) || defined(__MACH__)
    #define OS_MAC
    #include <mach/mach.h>

#endif


/**
 * This class is used to track the performance in terms of time and memory.
 */
class PerformanceTracker {

    // Variables to record time and the highest memory used
    high_resolution_clock::time_point startTime;
    high_resolution_clock::time_point endTime;
    size_t peakMemoryUsage = 0;
    size_t beginningMemory = 0;
    size_t finalMemory = 0;

    // A background thread to record performance
    thread performanceTrackingThread;
    atomic<bool> running = false;

public:

    // Method declaration
    void start();
    void stop();
    void updatePeakMemory();
    static size_t getCurrentMemoryUsage();

    // Constant methods: Methods that does not change the value of data
    void report(const string& label = "Performance") const;
};

