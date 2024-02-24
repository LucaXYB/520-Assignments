#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <queue>

class Integrator {
public:
    Integrator();
    ~Integrator();

    void start();
    void stop();
    double double_value() const;
    void pushValue(double value);

private:
    std::thread worker;
    mutable std::mutex mtx;
    std::condition_variable cv;
    std::queue<double> link;
    std::atomic<bool> running;
    double integral;

    void process();
    static constexpr double delta_time = 0.1;
};


#endif     // INTEGRATOR_H