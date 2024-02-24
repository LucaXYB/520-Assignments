#include "integrator.h"
#include <iostream>

Integrator::Integrator() : integral(0.0), running(false) {}

Integrator::~Integrator() {
    if (running) {
        stop();
    }
}

void Integrator::start() {
    running = true;
    worker = std::thread(&Integrator::process, this);
}

void Integrator::stop() {
    running = false;
    cv.notify_one();
    if (worker.joinable()) {
        worker.join();
    }
}

double Integrator::double_value() const{
    std::lock_guard<std::mutex> lock(mtx);
    return integral * 2.0;
}

void Integrator::pushValue(double value) {
    std::lock_guard<std::mutex> lock(mtx);
    link.push(value);
    cv.notify_one();
}

void Integrator::process() {
    std::unique_lock<std::mutex> lock(mtx);
    while (running) {
        cv.wait(lock, [this]{return !link.empty() || !running;});
        while (!link.empty()) {
            double value = link.front();
            link.pop();
            integral += delta_time * value;
        }
    }
}