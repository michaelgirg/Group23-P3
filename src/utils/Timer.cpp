#include "Timer.h"
#include <iostream>
#include <iomanip>
#include <sstream>

Timer::Timer() : isRunning(false) {}

void Timer::start() {
    startTime = std::chrono::high_resolution_clock::now();
    isRunning = true;
}

void Timer::stop() {
    endTime = std::chrono::high_resolution_clock::now();
    isRunning = false;
}

double Timer::getElapsedTime() const {
    if (isRunning) {
        auto current = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(current - startTime).count();
    } else {
        return std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
    }
}

double Timer::getElapsedTimeMs() const {
    return getElapsedTime() / 1000.0;
}

void Timer::reset() {
    isRunning = false;
}

std::string Timer::formatTime(double microseconds) {
    std::ostringstream oss;
    
    if (microseconds < 1000) {
        oss << std::fixed << std::setprecision(2) << microseconds << " μs";
    } else if (microseconds < 1000000) {
        oss << std::fixed << std::setprecision(2) << (microseconds / 1000.0) << " ms";
    } else {
        oss << std::fixed << std::setprecision(2) << (microseconds / 1000000.0) << " s";
    }
    
    return oss.str();
} 