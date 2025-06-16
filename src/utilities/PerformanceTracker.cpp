//
// Created by cmchan04 on 6/16/2025.
//

#include "PerformanceTracker.h"

PerformanceTracker::PerformanceTracker() {
    start();
}

void PerformanceTracker::start() {

    //starts timer
    startTime = high_resolution_clock::now();
    peakMemoryUsage = 0;
}

void PerformanceTracker::stop() {

    //stops timer and update peak memory
    endTime = high_resolution_clock::now();
    updatePeakMemory();
}

/**
 * @brief This function use the \code GetProcessMemoryInfo() \endcode from \code psapi.h \endcode to get the peak memory
 * @remark This only works for Windows
 */
void PerformanceTracker::updatePeakMemory() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        peakMemoryUsage = pmc.PeakWorkingSetSize;
    }
}

/**
 * This function will print the total time taken from start to end of the tracker and show the peak memory usage
 * @param label - Title for report
 */
void PerformanceTracker::report(const string& label) const {
    auto duration = duration_cast<milliseconds>(endTime - startTime).count();
    cout << "\n=== " << label << " ===\n";
    cout << "Time Taken: " << duration << " ms" << endl;
    cout << "Peak Memory Usage: " << peakMemoryUsage / 1024 << " KB" << endl;
    cout << endl;
}

//A backup function to check the memory in bytes
SIZE_T PerformanceTracker::getPeakMemoryBytes() const {
    return peakMemoryUsage;
}

