#include "Stopwatch.h"
#include <iostream>
#include <thread>

int main() {
    std::cout << "=== Stopwatch Demo ===" << std::endl;
    
   
    Stopwatch sw;
    
    std::cout << "Starting stopwatch..." << std::endl;
    sw.start();
    
    // Simulate some work
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    std::cout << "Elapsed: " << sw.getFormattedTime() << std::endl;
    
    // Record a lap
    sw.lap();
    std::cout << "Lap 1 recorded" << std::endl;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Elapsed: " << sw.getFormattedTime() << std::endl;
    
    // Record another lap
    sw.lap();
    std::cout << "Lap 2 recorded" << std::endl;
    
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    // Stop the stopwatch
    sw.stop();
    std::cout << "Stopwatch stopped" << std::endl;
    std::cout << "Final time: " << sw.getFormattedTime() << std::endl;
    std::cout << "Total seconds: " << sw.getElapsedSeconds() << std::endl;
    
    // Display lap times
    const auto& laps = sw.getLapTimes();
    std::cout << "\nLap Times:" << std::endl;
    for (size_t i = 0; i < laps.size(); ++i) {
        std::cout << "  Lap " << (i + 1) << ": " 
                  << laps[i] << " ms" << std::endl;
    }
    
    // Test resume functionality
    std::cout << "\nResuming stopwatch..." << std::endl;
    sw.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    sw.stop();
    std::cout << "After resume: " << sw.getFormattedTime() << std::endl;
    
    // Reset
    std::cout << "\nResetting stopwatch..." << std::endl;
    sw.reset();
    std::cout << "After reset: " << sw.getFormattedTime() << std::endl;
    
    // Test move semantics (RAII)
    std::cout << "\nTesting move semantics..." << std::endl;
    Stopwatch sw2;
    sw2.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    Stopwatch sw3 = std::move(sw2); // Move constructor
    std::cout << "Moved stopwatch time: " << sw3.getFormattedTime() << std::endl;
    sw3.stop();
    
    return 0;
}
