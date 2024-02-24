#ifndef RANDOM_PROCESS_H
#define RANDOM_PROCESS_H

#include "elma/elma.h"
#include <random>

using namespace elma;

class RandomProcess : public Process {
public:
    RandomProcess(std::string name) : Process(name) {}
    void init() override {}
    void start() override {}
    void update() override;
    void stop() override {}
};

#endif