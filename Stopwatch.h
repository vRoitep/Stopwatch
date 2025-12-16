#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>
#include <string>
#include <vector>

class Stopwatch {
public:
    // Constructor - initializes the stopwatch
    Stopwatch();
    
    // Destructor - RAII ensures cleanup
    ~Stopwatch();
    
    // Delete copy constructor and copy assignment (RAII principle)
    Stopwatch(const Stopwatch&) = delete;
    Stopwatch& operator=(const Stopwatch&) = delete;
    
    // Move constructor and move assignment
    Stopwatch(Stopwatch&&) noexcept;
    Stopwatch& operator=(Stopwatch&&) noexcept;
    
    // Start the stopwatch
    void start();
    
    // Stop the stopwatch
    void stop();
    
    // Reset the stopwatch
    void reset();
    
    // Record a lap time
    void lap();
    
    // Get elapsed time in milliseconds
    double getElapsedMs() const;
    
    // Get elapsed time in seconds
    double getElapsedSeconds() const;
    
    // Check if stopwatch is running
    bool isRunning() const;
    
    // Get formatted time string (HH:MM:SS.mmm)
    std::string getFormattedTime() const;
    
    // Get all lap times
    const std::vector<double>& getLapTimes() const;
    
private:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;
    
    TimePoint startTime;
    TimePoint stopTime;
    bool running;
    double accumulatedTime; // in milliseconds
    std::vector<double> lapTimes; // in milliseconds
    
    // Helper function to get current elapsed time
    double getCurrentElapsed() const;
};

#endif // STOPWATCH_H