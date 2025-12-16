#include "Stopwatch.h"
#include <sstream>
#include <iomanip>

Stopwatch::Stopwatch() 
    : running(false), accumulatedTime(0.0) {
}

Stopwatch::~Stopwatch() {
    // RAII: Cleanup happens automatically
    // In this case, all members are automatically destroyed
}

Stopwatch::Stopwatch(Stopwatch&& other) noexcept
    : startTime(other.startTime),
      stopTime(other.stopTime),
      running(other.running),
      accumulatedTime(other.accumulatedTime),
      lapTimes(std::move(other.lapTimes)) {
    other.running = false;
    other.accumulatedTime = 0.0;
}

Stopwatch& Stopwatch::operator=(Stopwatch&& other) noexcept {
    if (this != &other) {
        startTime = other.startTime;
        stopTime = other.stopTime;
        running = other.running;
        accumulatedTime = other.accumulatedTime;
        lapTimes = std::move(other.lapTimes);
        
        other.running = false;
        other.accumulatedTime = 0.0;
    }
    return *this;
}

void Stopwatch::start() {
    if (!running) {
        startTime = Clock::now();
        running = true;
    }
}

void Stopwatch::stop() {
    if (running) {
        stopTime = Clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            stopTime - startTime
        ).count();
        accumulatedTime += elapsed;
        running = false;
    }
}

void Stopwatch::reset() {
    running = false;
    accumulatedTime = 0.0;
    lapTimes.clear();
}

void Stopwatch::lap() {
    if (running) {
        double currentElapsed = getCurrentElapsed();
        lapTimes.push_back(currentElapsed);
    }
}

double Stopwatch::getElapsedMs() const {
    return getCurrentElapsed();
}

double Stopwatch::getElapsedSeconds() const {
    return getCurrentElapsed() / 1000.0;
}

bool Stopwatch::isRunning() const {
    return running;
}

std::string Stopwatch::getFormattedTime() const {
    double totalMs = getCurrentElapsed();
    int hours = static_cast<int>(totalMs / 3600000);
    int minutes = static_cast<int>((totalMs - hours * 3600000) / 60000);
    int seconds = static_cast<int>((totalMs - hours * 3600000 - minutes * 60000) / 1000);
    int milliseconds = static_cast<int>(totalMs) % 1000;
    
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hours << ":"
        << std::setfill('0') << std::setw(2) << minutes << ":"
        << std::setfill('0') << std::setw(2) << seconds << "."
        << std::setfill('0') << std::setw(3) << milliseconds;
    
    return oss.str();
}

const std::vector<double>& Stopwatch::getLapTimes() const {
    return lapTimes;
}

double Stopwatch::getCurrentElapsed() const {
    if (running) {
        auto now = Clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - startTime
        ).count();
        return accumulatedTime + elapsed;
    }
    return accumulatedTime;
}