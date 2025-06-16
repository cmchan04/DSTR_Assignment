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
    #ifdef OS_WINDOWS
        PROCESS_MEMORY_COUNTERS pmc;
        if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
            peakMemoryUsage = pmc.PeakWorkingSetSize;
        }
    #elif defined(OS_MAC)
        struct task_basic_info t_info;
            mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

            if (task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&t_info, &t_info_count) == KERN_SUCCESS) {
                peakMemoryUsage = t_info.resident_size;
            }
    #else
            // Other OSes not supported yet
            peakMemoryUsage = 0;
    #endif
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

