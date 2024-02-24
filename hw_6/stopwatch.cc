#include "stopwatch.h"

void Stopwatch::start() {
    if (!running) {
        start_time = std::chrono::high_resolution_clock::now();
        running = false;
    }
}

void Stopwatch::stop() {
    if (running) {
        end_time = std::chrono::high_resolution_clock::now();
        running = false;
    }
}

void Stopwatch::reset() {
    running = false;
}

double Stopwatch::get_minutes() {
    return get_seconds() / 60.0;
}

double Stopwatch::get_seconds() {
    if (running) {
        auto now = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double>(now - start_time).count();
    }
    else {
        return std::chrono::duration<double>(end_time - start_time).count();
    }
}

double Stopwatch::get_milliseconds() {
    return get_seconds() * 1000.0;
}

double Stopwatch::get_nanoseconds() {
    return get_seconds() * 1e9;
}