// StopWatch.h
#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>
//using namespace chrono;

class Stopwatch {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;
    bool running = false;

public:
    void start();              // starts the timer
    void stop();               // stops the timer
    void reset();              // sets stopwatch to zero
    double get_minutes();      // number of minutes counted, as a double
    double get_seconds();      // number of seconds counted, as a double
    double get_milliseconds(); // number of milliseconds counted, as a double
    double get_nanoseconds();  // number of nanoseconds counted, as a double
};

#endif  // STOPWATCH_H