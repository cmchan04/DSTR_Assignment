//
// Created by cmchan04 on 6/16/2025.
//

#include "PerformanceTracker.h"
#include <iostream>

/**
 * A method to retrieve the current usage of memory in KB size.
 * @return
 */
size_t PerformanceTracker::getCurrentMemoryUsage() {

    #ifdef OS_WINDOWS

        // Variable to hold memory information
        PROCESS_MEMORY_COUNTERS pmc;

        // Retrieve the current memory used
        GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
        return pmc.WorkingSetSize / 1024;

    #elif defined(OS_MAC)

        // Declare a struct to store information about memory
        task_basic_info_data_t info{};

        // Get the number of details to be stored
        mach_msg_type_number_t size = TASK_BASIC_INFO_COUNT;

        // Retrieve the current memory used. If failed, return 0
        if (task_info(mach_task_self(), TASK_BASIC_INFO, reinterpret_cast<task_info_t>(&info), &size) != KERN_SUCCESS) {
            return 0;
        }

        // Return the retrieved current memory in KB if successful
        return info.resident_size / 1024;

    // Other OS are not supported as for now
    #else
    #endif
}

/**
 * Marks the start to record time and memory usage
 */
void PerformanceTracker::start() {

    // Start recording and get beginning memory
    startTime = high_resolution_clock::now();
    peakMemoryUsage = 0;
    beginningMemory = getCurrentMemoryUsage();

    // Ensure performance is measured consistently (for Mac) by running updatePeakMemory() every 0.1 seconds
    running = true;
    performanceTrackingThread = thread([this] {
        while (running) {
            updatePeakMemory();
            this_thread::sleep_for(milliseconds(100));
        }
    });
}

/**
 * Halts the measuring of performance
 */
void PerformanceTracker::stop() {

    // Retrieve the final memory
    finalMemory = getCurrentMemoryUsage();

    // Stops updatePeakMemory() from running. Also make sure that thread finishes before the main thread ends.
    running = false;
    if (performanceTrackingThread.joinable()) {
        performanceTrackingThread.join();
    }

    // Records ending time
    endTime = high_resolution_clock::now();
}

/**
 * This function uses the \code GetProcessMemoryInfo()\endcode from \code psapi.h\endcode to get the peak memory (Windows).<br>
 * For Mac, the \code mach.h\endcode file is used to collect memory information.
 *
 */
void PerformanceTracker::updatePeakMemory() {

    // Windows computers
    #ifdef OS_WINDOWS

        // Variable to hold memory information
        PROCESS_MEMORY_COUNTERS pmc;

        // If memory information can be written, retrieve the peak memory
        if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
            peakMemoryUsage = pmc.PeakWorkingSetSize / 1024;
        }

    // Mac computers can't retrieve peak memory directly.
    // The current resident memory value will be continuously overwritten with numbers larger than it.
    #elif defined(OS_MAC)

        // Declare a task_basic_info struct to store details of the currently running task
        task_basic_info t_info{};

        // List down the number of data collected in the t_info struct
        mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

        // Check if the details of the current thread (mach_task_self) can be written into t_info
        if (task_info(mach_task_self(),
            TASK_BASIC_INFO, reinterpret_cast<task_info_t>(&t_info), &t_info_count) == KERN_SUCCESS) {

            // If yes, retrieve the resident size (current memory usage) to get the peak memory
            size_t currentMemory = t_info.resident_size;
            if (currentMemory > peakMemoryUsage) {
                peakMemoryUsage = currentMemory / 1024;
            }
        }

    // Other OS are not supported, hence no measurement takes place
    #else
        peakMemoryUsage = 0;

    #endif
}

/**
 * This function will print the total time taken from start to end of the tracker and show the peak memory usage
 * @param label Title for the report
 */
void PerformanceTracker::report(const string &label) const {

    // Calculate duration taken
    const auto duration = duration_cast<milliseconds>(endTime - startTime).count();

    // Print performance information
    cout << "\n=== " << label << " ===\n";
    cout << "Time Taken: " << duration << " ms (" << duration / 1000 << " seconds)" << endl;
    cout << "Beginning memory: " << beginningMemory << " KB (" << beginningMemory / 1024 << " MB)" << endl;
    cout << "Final memory: " << finalMemory << " KB (" << finalMemory / 1024 << " MB)" << endl;
    cout << "Difference between Beginning and Final Memory Usage: " <<
        (finalMemory > beginningMemory ? finalMemory - beginningMemory : beginningMemory - finalMemory) <<
            " KB (" <<
        (finalMemory > beginningMemory ? finalMemory - beginningMemory : beginningMemory - finalMemory) / 1024 <<
            " MB)" << endl;
    cout << "Peak Memory Usage: " << peakMemoryUsage << " KB (" << peakMemoryUsage / 1024 << " MB)" << endl;
    cout << endl;
}
