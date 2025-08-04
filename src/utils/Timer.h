#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;
    bool isRunning;
    
public:
    // Constructor initializes timer in stopped state
    Timer();
    
    // Starts timing measurement with high resolution clock
    void start();
    
    // Stops timing measurement and records end time
    void stop();
    
    // Returns elapsed time in microseconds for precise measurements
    double getElapsedTime() const;
    
    // Returns elapsed time in milliseconds for readability
    double getElapsedTimeMs() const;
    
    // Resets timer to initial state for reuse
    void reset();
    
    // Returns true if timer is currently running
    bool running() const { return isRunning; }
    
    // Converts microseconds to readable format with units
    static std::string formatTime(double microseconds);
};

#endif 