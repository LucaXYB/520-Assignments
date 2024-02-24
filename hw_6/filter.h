#ifndef FILTER_H
#define FILTER_H
#include "elma/elma.h"
using namespace elma;
class Filter : public Process {
public:
    Filter(std::string name) : Process(name), _average(0) {}
    void init() override {}
    void start() override {}
    void update() override;
    void stop() override {}
    double value() const;

private:
    std::deque<double> _lastValues;
    double _average;
};

#endif